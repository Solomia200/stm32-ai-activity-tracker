#!/bin/bash
set -e
shopt -s nullglob

DATASET_PATH="$1"

preprocess_directory() {
    cd "$1/data"

    for f in acc*_csv.zip; do
        name=$(basename "$f" .zip)
        unzip -d "$name" "$f"

        # unzip nested archives if present
        files=("$name"/*.zip)
        for file in "${files[@]}"; do
            sub_archive_name=$(basename "$file" .zip)
            unzip -d "$sub_archive_name" "$file"
        done

        if (( ${#files[@]} )); then
            rm -rf "$name"
        fi
    done

    for f in gyr*_csv.zip; do
        name=$(basename "$f" .zip)
        unzip -d "$name" "$f"

        # unzip nested archives if present
        files=("$name"/*.zip)
        for file in "${files[@]}"; do
            sub_archive_name=$(basename "$file" .zip)
            unzip -d "$sub_archive_name" "$file"
        done

        if (( ${#files[@]} )); then
            rm -rf "$name"
        fi
    done

    rm -f *.zip
    cd ../..
}


cd "$DATASET_PATH"

for d in */; do
    preprocess_directory "$d"
done

echo "Preprocessing finished succesfully"
