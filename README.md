# WebSDRRotaryControl

Steuerung des WebSDR der Universität Twente (http://websdr.ewi.utwente.nl:8901) mit Drehimpulsgeber (Frequenz, Filterbandbreite). Weitere Einstellungen wie Demodulationsart usw. über Taster ebenfalls umsetzbar.

![titel](https://github.com/BM45/WebSDRRotaryControl/blob/master/pics4www/titel.jpg)

/WebSDRControl/WebSDRControl.ino -> Firmware für Arduino, der hier als Bindeglied zwischen Drehimpulsgeber, Taster und PC dient

build.sh -> compiliert das Terminalprogramm term2websdr, als Bindeglied zwischen serieller Schnittstelle (/dev/ttyUSB0) und der Tastatursteuerung des WebSDR

build_TwenteSDRBrowser.sh (optional) -> compiliert einen minimalistischen Webbrowser (Webkit) speziell nur für das WebSDR der Uni Twente 
