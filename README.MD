# Animal Button Box

Project for [Making Embedded Systems](https://classpert.com/classpertx/courses/making-embedded-systems/)

It uses among other things:
 - [Adafruit Feather RP2040](https://learn.adafruit.com/adafruit-feather-rp2040-pico) 
 - [Bosch BNO055](https://www.bosch-sensortec.com/products/smart-sensor-systems/bno055/)
 - [Waveshare E-Paper Display](https://www.waveshare.com/wiki/1.54inch_e-Paper_Module)

What is it supposed to do?

Imagine a little cube that you can hold in your hand.
On its front display you can see an e-ink display displaying the silhouette of a turtle.
On its top face sits a round arcade button. The device seems to be sleeping.
You shake the cube and the button lights up and the device emits a squeak.
You press the button and a new random animal silhouette appears on the screen.
After you set the cube back on the table, the device purrs and goes back to sleep.

It is work in progress.

## Used Libraries

## Configuring the environment

This was built and depends on the [RPi Pico SDK V1.5.1](https://github.com/raspberrypi/pico-sdk)

Its location must be set as an environment, e.g.:

```shell
export PICO_SDK_PATH="your_local_path"
```

The project is configured for the Adafruit Feather RP2040.
To change this, please change the follwing line `./CMakeLists.txt` in the projects root directory.

```cmake
set(PICO_BOARD "adafruit_feather_rp2040")
```
And `PICO_BOARD=adafruit_feather_rp2040` in `./build.sh`

Add a `./build` folder and run `cmake ..` from inside it.

## Building and flashing

Run `./build.sh`

If you are using [picotool](https://github.com/raspberrypi/picotool) you can simple flash in two steps:

1. Bring the board into BOOTSEL mode by holding the the same called button while resetting
2. Write the built `.uf2` onto the board with the following command:
    ```shell
    "PATH_TO_PICOTOOL/picotool load .build/debug/src/console_poc.uf2
    ```
## License