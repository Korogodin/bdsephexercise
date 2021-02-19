# Dependencies

If you want to make any changes and build the firmware from sources, you need corresponding instruments. 

## сmake

You need cmake for compiling both host software and firmware. Just install from the repository:
```sh
sudo apt-get install cmake
```

## check

Check is a testing framework. You can install it from the Ubuntu repositiory like:
```sh
sudo apt-get install check
```

## pkg-config

The pkg-config program is used to retrieve information about installed libraries in the system.
```sh
sudo apt-get install pkg-config
```

## Сompiler

It is recommended to use gcc. 

```sh
sudo apt-get install gcc
```

# Compiling and developing


## Host tests

1.  Install dependencies: cmake, checkmk, gcc and your favorit text editor or IDE (don't forget to install qt5-default for QtCreator).

2.  Create build directory, change the path (cd libbdssvpos; mkdir build)

3.  Execute cmake command (cmake ..)

4.  Make it (make)

