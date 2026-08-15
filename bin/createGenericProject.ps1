# Verzeichnis-Pfade für C- und ASM-Projekte
$SCRIPT_DIR = Split-Path -Parent $MyInvocation.MyCommand.Path
$C_TEMPLATE_DIR = Join-Path $SCRIPT_DIR "template\c-project"
$ASM_TEMPLATE_DIR = Join-Path $SCRIPT_DIR "template\asm-project"
$DEST_DIR = Join-Path $SCRIPT_DIR "..\Programs"

# Funktion zur Überprüfung des Projektnamens
function Validate-ProjectName {
    param (
        [string]$project_name
    )

    # Überprüfen, ob der erste Buchstabe groß ist
    $first_letter = $project_name.Substring(0,1)
    Write-Host "Überprüfe den ersten Buchstaben: $first_letter"

    if ($first_letter -cmatch '^[A-Z]') {
        return $true
    } else {
        Write-Host "Der erste Buchstabe des Projektnamens muss ein Großbuchstabe sein."
        return $false
    }
}

# Funktion zum direkten Kopieren der Inhalte des Template-Verzeichnisses 
# und Ersetzen von 'template' durch den Projektnamen
function Copy-And-Replace-Recursive {
    param (
        [string]$template_path,
        [string]$dest_dir,
        [string]$project_name
    )

    if (Test-Path $template_path) {
        # Hole alle Dateien und Verzeichnisse im Template-Verzeichnis
        Get-ChildItem -Path $template_path -Recurse | ForEach-Object {
            Write-Host "Verarbeite: $($_.FullName)" # Debugging-Ausgabe

            # Berechne den relativen Pfad der Datei/des Verzeichnisses ab dem Template-Verzeichnis
            $relativePath = $_.FullName.Substring($template_path.Length + 1)

            Write-Host "Relativer Pfad (original): $relativePath" # Debugging-Ausgabe

            # Ersetze 'template' durch den Projektnamen im relativen Pfad
            $replacedRelativePath = $relativePath -replace 'template', $project_name

            Write-Host "Relativer Pfad (ersetzt): $replacedRelativePath" # Debugging-Ausgabe

            $targetPath = Join-Path $dest_dir $replacedRelativePath 

            Write-Host "Zielpfad: $targetPath" # Debugging-Ausgabe

            if ($_.PSIsContainer) {
                # Verzeichnis direkt im Zielverzeichnis erstellen, falls es noch nicht existiert
                if (-not (Test-Path $targetPath)) {
                    New-Item -ItemType Directory -Force -Path $targetPath | Out-Null
                    Write-Host "Verzeichnis erstellt: $targetPath" # Debugging-Ausgabe
                } else {
                    Write-Host "Verzeichnis existiert bereits: $targetPath" # Debugging-Ausgabe
                }
            } else {
                # Stelle sicher, dass das Zielverzeichnis existiert
                $targetDir = Split-Path -Parent $targetPath
                if (-not (Test-Path $targetDir)) {
                    New-Item -ItemType Directory -Force -Path $targetDir | Out-Null
                    Write-Host "Zielverzeichnis erstellt: $targetDir" # Debugging-Ausgabe
                }

                # Datei kopieren
                Copy-Item -Path $_.FullName -Destination $targetPath -Force
                Write-Host "Datei kopiert: $targetPath" # Debugging-Ausgabe

                # Ersetze "template" im Dateiinhalt durch den Projektnamen
                (Get-Content $targetPath) -replace 'template', $project_name | Set-Content $targetPath
                Write-Host "Ersetzungen in Datei durchgeführt: $targetPath" # Debugging-Ausgabe
            }
        }
    } else {
        Write-Host "Fehler: Template-Verzeichnis '$template_path' nicht gefunden."
    }
}

# Funktion zum Ändern der Berechtigungen rekursiv auf alle Unterverzeichnisse und Dateien
function Set-Permissions {
    param (
        [string]$path
    )

    # Hole den aktuell angemeldeten Benutzer
    $user = $env:UserName
    Write-Host "Setze Berechtigungen für den angemeldeten Benutzer: $user"

    # Berechtigungen für den Hauptordner festlegen
    $acl = Get-Acl $path
    $accessRule = New-Object System.Security.AccessControl.FileSystemAccessRule($user, "FullControl", "Allow")
    $acl.SetAccessRule($accessRule)
    Set-Acl -Path $path -AclObject $acl
    Write-Host "Berechtigungen für '$path' wurden erfolgreich geändert."

    # Berechtigungen rekursiv auf alle Unterverzeichnisse und Dateien setzen
    Get-ChildItem -Recurse -Path $path | ForEach-Object {
        if (-not $_.PSIsContainer) {
            $fileAcl = Get-Acl $_.FullName
            $fileAcl.SetAccessRule($accessRule)
            Set-Acl -Path $_.FullName -AclObject $fileAcl
        } elseif ($_.PSIsContainer) {
            $folderAcl = Get-Acl $_.FullName
            $folderAcl.SetAccessRule($accessRule)
            Set-Acl -Path $_.FullName -AclObject $folderAcl
        }
    }
}

# Hauptfunktion
function Main {
    param (
        [string]$project_type,
        [string]$project_name
    )

    if (-not $project_type) {
        Write-Host "Verwendung: --c | --asm <Projektname>"
        exit 1
    }

    if (-not $project_name) {
        Write-Host "Bitte geben Sie einen gültigen Projektnamen ein."
        exit 1
    }

    Write-Host "Arbeite mit Projekttyp: $project_type und Projektname: $project_name"

    if (-not (Validate-ProjectName -project_name $project_name)) {
        exit 1
    }

    # Wähle die richtige Vorlage basierend auf dem Projekttyp
    if ($project_type -eq "--c") {
        $template_dir = $C_TEMPLATE_DIR
    } elseif ($project_type -eq "--asm") {
        $template_dir = $ASM_TEMPLATE_DIR
        $project_name = "$project_name`ASM" 
    } else {
        Write-Host "Ungültiger Projekttyp. Verwenden Sie --c für C-Projekte oder --asm für ASM-Projekte."
        exit 1
    }

    $project_dir = Join-Path $DEST_DIR $project_name

    if (Test-Path $project_dir) {
        Write-Host "Das Projektverzeichnis '$project_dir' existiert bereits."
        exit 1
    }

    # Neues Projektverzeichnis erstellen
    New-Item -ItemType Directory -Force -Path $project_dir | Out-Null

    # Kopiere den Inhalt des Template-Verzeichnisses ins Zielverzeichnis und ersetze 'template'
    Copy-And-Replace-Recursive -template_path $template_dir -dest_dir $project_dir -project_name $project_name

    # Erstellte .vscode.d Verzeichnis - nicht schoen, aber einfach und robust
    mkdir "$project_dir\.vscode.d"
    cp "$template_dir\.vscode.d\tasks.json"  "$project_dir\.vscode.d"

    Write-Host "Projekt '$project_name' erfolgreich erstellt in '$project_dir'."

    # Berechtigungen für das neu erstellte Verzeichnis und dessen Inhalte setzen
    Set-Permissions -path $project_dir
}

# Skript starten
Main -project_type $args[0] -project_name $args[1]
