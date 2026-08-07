#!/bin/bash

# Verzeichnis-Pfade für C- und ASM-Projekte
C_TEMPLATE_DIR="./template/c-project"
ASM_TEMPLATE_DIR="./template/asm-project"
DEST_DIR="../Programs"

# Funktion zur Überprüfung des Projektnamens
validate_project_name() {
    local project_name=$1

    # Überprüfen, ob der erste Buchstabe groß ist
    if [[ ! $project_name =~ ^[A-Z] ]]; then
        echo "Der erste Buchstabe des Projektnamens muss ein Großbuchstabe sein."
        return 1
    fi

    # Überprüfen, ob der Name keine Leerzeichen oder Sonderzeichen enthält
    if [[ ! $project_name =~ ^[A-Za-z0-9]+$ ]]; then
        echo "Der Projektname darf nur Buchstaben und Zahlen enthalten, keine Leerzeichen oder Sonderzeichen."
        return 1
    fi

    return 0
}

# Funktion zum rekursiven Kopieren der Vorlagen und Ersetzen des Namens
copy_and_replace_recursive() {
    local template_path=$1
    local dest_dir=$2
    local project_name=$3

    if [ -d "$template_path" ]; then
        mkdir -p "$dest_dir"

        for item in "$template_path"/*; do
            base_item=$(basename "$item")
            new_item="$dest_dir/$(echo "$base_item" | sed "s|template|$project_name|g")"
            copy_and_replace_recursive "$item" "$new_item" "$project_name"
        done
    else
        new_file_name=$(basename "$template_path" | sed "s|template|$project_name|g")

        cp "$template_path" "$dest_dir"

        # Verwenden Sie find und perl, um Ersetzungen im Dateiinhalt durchzuführen
        find "$dest_dir" -type f -exec perl -pi -e "s|template|$project_name|g" {} \;
    fi
}

# Hauptfunktion
main() {
    local project_name
    local project_type
    local template_dir

    # Überprüfen, ob ein Projekttyp und ein Projektname übergeben wurden
    if [ -z "$1" ] || [ -z "$2" ]; then
        echo "Verwendung: $0 --c|--asm <Projektname>"
        exit 1
    fi

    project_type=$1
    project_name=$2

    # Überprüfen, ob der Projektname gültig ist
    validate_project_name "$project_name"
    if [ $? -ne 0 ]; then
        exit 1
    fi

    # Wähle die richtige Vorlage basierend auf dem Projekttyp
    case "$project_type" in
        --c)
            template_dir="$C_TEMPLATE_DIR"
            ;;
        --asm)
            template_dir="$ASM_TEMPLATE_DIR"
            project_name="${project_name}ASM"  # Füge "ASM" zum Projektnamen hinzu
            ;;
        *)
            echo "Ungültiger Projekttyp. Verwenden Sie --c für C-Projekte oder --asm für ASM-Projekte."
            exit 1
            ;;
    esac

    # Zielverzeichnis definieren
    project_dir="$DEST_DIR/$project_name"

    # Überprüfe, ob das Projektverzeichnis bereits existiert
    if [ -d "$project_dir" ]; then
        echo "Das Projektverzeichnis '$project_dir' existiert bereits."
        exit 1
    fi

    # Erstelle das Projektverzeichnis
    mkdir -p "$project_dir"

    # Durchlaufe das Vorlagenverzeichnis und kopiere die Dateien/Verzeichnisse rekursiv
    copy_and_replace_recursive "$template_dir" "$project_dir" "$project_name"

    # Erstellte .vscode.d Verzeichnis - nicht schoen, aber einfach und robust
    mkdir $project_dir/.vscode.d
    cp $template_dir/.vscode.d/tasks.json  $project_dir/.vscode.d
    cp $template_dir/clang_tidy_result.txt $project_dir

    echo "Projekt '$project_name' erfolgreich erstellt in '$project_dir'."
}

# Skript ausführen
main "$@"

