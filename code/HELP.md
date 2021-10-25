# Help with `arduino-cli` 
If you want to use `arduino-cli` to compile this project, here is a guide:

- installation:
```
# install the avr platform 
arduino-cli core install arduino:avr

# install the adafruit core
arduino-cli core install adafruit:avr --additional-urls https://www.adafruit.com/package_adafruit_index.json

# install lib
arduino-cli lib install "Adafruit BluefruitLE nRF5"

```

- test if board is connected:
```
# test if board detected
arduino-cli board list
```

- compile and upload a sketch:
```
# create sketch.json
arduino-cli attach adafruit:avr:feather32u4
arduino-cli compile 
arduino-cli upload
```

