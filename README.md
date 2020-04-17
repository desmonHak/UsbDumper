# UsbDumper 2.0
> UsbDumper 2.0 es una pequeña utilidad que permite copiar al instante los archivos de los dispositivos recien conectados, actuando de manera sigilosa. Además que es un fork que trae consigo mismo características para una mayor eficiencia y usabilidad.

## Características de esta versión

* **Eficiencia**: Es realmente rápido
* **Recursividad**: Además de copiar todos los archivos que pueda, también crea las carpetas según el nombre de éstas en el directorio de salida
* **El pingüino se asoma por la ventana**: Funciona tanto para Windows como para GNU/Linux
* **Múltiples objetivos**: Los objetivos se definen en [config.h](config.h) según el sistema operativo y se pueden colocar más de uno si se desea
* **Fácil**: Es realmente fácil, simplemente ejecutando el nombre del ejecutable, el parámetro (**-t**) para seleccionar la ruta y listo, empiece a extraer todos esos datos del dispositivo víctima, mientras que para \*nix si se desea se puede usar el [script](install/UsbDumper) para crear un *daemon* y ejecutarlo en segundo plano.

## Instalación

### Descarga

```bash
git clone https://github.com/DtxdF/UsbDumper.git
cd UsbDumper
```

### GNU/Linux

```bash
sudo make -f linux.mk install
man UsbDumper # UsbDumper -h
```

**Nota**: Por defecto se instala e inicia el *daemon* en "**/etc/init.d**", si desea puede apagarlo y deshabilitarlo (o borrarlo)

```bash
systemctl disable UsbDumper
systemctl stop UsbDumper
# Para eliminarlo
rm -f /etc/init.d/UsbDumper
```

El *daemon* no es necesario, es para que se mantenga oculta, pero hay diferentes maneras de poder lograrlo, como usar cron, usar nohup o una variedad de herramientas de apoyo. **¡ES LIBRE DE USAR LA QUE DESEA!**

### Windows

```batch
mingw32-make -f windows.mk
UsbDumper.exe -h
```

## Notas

* El programa termina su ejecución cuando se haya completado la extración de cada dispositivo víctima
* Debe tener en cuenta la primera nota para el *daemon*, **el *daemon* es usado para ocultar lo que se está haciendo**.
* Cuando se termine de extraer todos los archivos, el programa tomará en cuenta la ruta como identificador para no volver a copiar los archivos
* El archivo [config.h](config.h) es el encargado de verificar los dispositivos víctimas, y es el usuario el que decide qué dispositivos serán los que se desea extraer los archivos

\~ DtxdF
