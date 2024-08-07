# WebSDRRotaryControl

Steuerung des WebSDR der Universität Twente (http://websdr.ewi.utwente.nl:8901) mit Drehimpulsgeber (Frequenz, Filterbandbreite). Weitere Einstellungen wie Demodulationsart usw. über Taster ebenfalls umsetzbar.

![titel](https://github.com/radiolab81/WebSDRRotaryControl/blob/master/pics4www/titel.jpg)

![pin](https://github.com/radiolab81/WebSDRRotaryControl/blob/master/pics4www/arduino_pin.jpg)

/WebSDRControl/WebSDRControl.ino -> Firmware für Arduino, der hier als Bindeglied zwischen Drehimpulsgeber, Taster und PC dient

build.sh -> compiliert das Terminalprogramm term2websdr, als Bindeglied zwischen serieller Schnittstelle (/dev/ttyUSB0) und der Tastatursteuerung des WebSDR

build_TwenteSDRBrowser.sh (optional) -> compiliert einen minimalistischen Webbrowser (Webkit) speziell nur für das WebSDR der Uni Twente 

#### Durch Anpassung der Tastaturkommandos in term2websdr.c können prinzipiell andere WebSDRs wie KiwiSDR ebenso über Drehencoder/Taster bedient werden. Auch SDR-Softwares wie HDSDR, SDR# (SDRsharp) und andere können so einfach, schnell und kostengünstig mit einem richtigen Abstimmrad und Funktionsknöpfen erweitert werden.


