#!/bin/bash

preprocess_directory() {
    cd "$1/data"

    # mkdir -p data-csv/accelerometer
    for f in acc*_csv.zip; do
        name=$(basename "$f" .zip)
        unzip -d "$name" "$f"
    done

    # mkdir -p data-csv/gyroscope
    for f in gyr*_csv.zip; do
        name=$(basename "$f" .zip)
        unzip -d "$name" "$f"
    done

    rm *.zip

    cd ../..
}

set -e

cd dataset-csv

for d in */; do
    preprocess_directory "$d"
done

echo "Preprocessing finished succesfully"

