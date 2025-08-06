#pragma once

constexpr const char *default_config = R"(# This is the default config.
# Make a user.yml in the same directory to add or modify categories.
#
# Example user.yml:
# categories:
#   - name: 3d
#     dir: 3d # (optional, default: name)
#     override: true # (optional, default: false. When true, it overrides the extensions of the category, extends otherwise)
#     extensions:
#       - .blender
#       - .fbx
#       - .obj
#
#   - name: jpg
#     dir: photo/jpg
#     extensions:
#       - .jpg
#       - .jpeg
#
# NOTE: The override option is only for overriding extensions, everything else (like dir) is overrided automatically. 
#       Omit a property to not override it.
#
# In any way if you loose this default.yml, you can generate it by:
#
#             `dorg get-config`
#
#              OR save it as a file:
#
#             `dorg get-config > ~/.config/dorg/default.yml`

categories:
  - name: audio
    extensions:
      - .mp3
      - .wav
      - .flac
      - .aac
      - .ogg
      - .m4a
      - .wma
      - .alac
      - .aiff
      - .opus

  - name: archive
    extensions:
      - .zip
      - .rar
      - .7z
      - .tar
      - .iso
      - .cab
      - .arj

  - name: compressed
    extensions:
      - .gz
      - .bz2
      - .xz
      - .lz
      - .lzma
      - .zst

  - name: document
    extensions:
      - .pdf
      - .doc
      - .docx
      - .txt
      - .odt
      - .rtf
      - .tex
      - .md

  - name: photo
    extensions:
      - .jpg
      - .jpeg
      - .png
      - .gif
      - .bmp
      - .tiff
      - .svg
      - .webp
      - .heic
      - .raw

  - name: presentation
    extensions:
      - .ppt
      - .pptx
      - .odp
      - .key

  - name: spreadsheet
    extensions:
      - .xls
      - .xlsx
      - .xlsm
      - .ods
      - .csv
      - .tsv
      - .xlsb
      - .xlt
      - .xltx

  - name: video
    extensions:
      - .mp4
      - .mkv
      - .mov
      - .avi
      - .webm
      - .flv
      - .wmv
      - .m4v
      - .3gp

  - name: font
    extensions:
      - .ttf
      - .otf
      - .woff
      - .woff2
      - .eot
      - .sfnt
      - .fnt
      - .pfa
      - .pfb
)";
