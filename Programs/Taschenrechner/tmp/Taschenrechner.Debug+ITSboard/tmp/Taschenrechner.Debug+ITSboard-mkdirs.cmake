# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "D:/Dokumente/_HAW/Projekte/ITS-BRD-VSC/Programs/Taschenrechner/tmp/Taschenrechner.Debug+ITSboard"
  "D:/Dokumente/_HAW/Projekte/ITS-BRD-VSC/Programs/Taschenrechner/tmp/1"
  "D:/Dokumente/_HAW/Projekte/ITS-BRD-VSC/Programs/Taschenrechner/tmp/Taschenrechner.Debug+ITSboard"
  "D:/Dokumente/_HAW/Projekte/ITS-BRD-VSC/Programs/Taschenrechner/tmp/Taschenrechner.Debug+ITSboard/tmp"
  "D:/Dokumente/_HAW/Projekte/ITS-BRD-VSC/Programs/Taschenrechner/tmp/Taschenrechner.Debug+ITSboard/src/Taschenrechner.Debug+ITSboard-stamp"
  "D:/Dokumente/_HAW/Projekte/ITS-BRD-VSC/Programs/Taschenrechner/tmp/Taschenrechner.Debug+ITSboard/src"
  "D:/Dokumente/_HAW/Projekte/ITS-BRD-VSC/Programs/Taschenrechner/tmp/Taschenrechner.Debug+ITSboard/src/Taschenrechner.Debug+ITSboard-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "D:/Dokumente/_HAW/Projekte/ITS-BRD-VSC/Programs/Taschenrechner/tmp/Taschenrechner.Debug+ITSboard/src/Taschenrechner.Debug+ITSboard-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "D:/Dokumente/_HAW/Projekte/ITS-BRD-VSC/Programs/Taschenrechner/tmp/Taschenrechner.Debug+ITSboard/src/Taschenrechner.Debug+ITSboard-stamp${cfgdir}") # cfgdir has leading slash
endif()
