## Vysoké učení technické v Brně
### Fakulta eletrotechniky a komunikaních technologií
#### Digitální elektronika 2
##### Projekt
Parkovací asistent
======




Tento projekt se zabývá řešením **parkovacího asistenta** pomocí **2 ultrazvukových senzorů (HC-SR04)** a **indikátoru vybuzení**.


Níže je tento projekt rozdělen do jednotlivých částí s odkazy na dílčí soubory, screenshoty jednotlivých průběhů aplikace, a dále odkazy na datasheete a jiné užitečné informace.



 ##      **Kompletní projekt**
  
 Výsledná práce sestává z jednotlivých bloků (modulů), které byly vytvořeny, následně propojeny a odsimulovány ke správné funkčnosti zadaného projektu.
 
 
 ![Blokove schéma zapojení parkovacího asistenta](https://github.com/Filip-ZL/Digital-electronics-2/blob/master/Labs/Project/project/images/block_scheme.png)
  *Obr.1 Kompletní blokové schéma aplikace*
  
  
 ![Kompletní schéma zapojení aplikace - SimulIDE](https://github.com/Filip-ZL/Digital-electronics-2/blob/master/Labs/Project/project/images/scheme.png)
 *Obr.2 Kompletní schéma zapojení aplikace*
 
 
 - **ATmega328p**
 - **2x HC-SR04 senzor**
 - **Display (HD44780)**
 - **Posuvný registr (74HC595)**
 - **MUX**
 - **LED Bar**
 
 
 ### ATmega328p
 Jedná se o řídící 8 bitový mikrokontrolér. Odkaz na [datasheet ATmega328p](https://www.microchip.com/wwwproducts/en/ATmega328p).
 
 
 ### Senzor HC-SR04
 Daný senzor funguje na tomto principu: Nejprve je vyslán 10us pulz do portu *trigger*, jenž následně vyšle skupinu zvukových impulzů (40 kHz), které se odrazí od překážky a je zpětně zachycen v přímači. Port *echo* zůstane ve vysoké úrovni (log. 1), dokud se impulz nevrátí.
 Pokud je objekt vzdálen více jak 4 metry, pulz *echo* je dlouhý 25 ms. Rozlišovací schopnost senzoru je od 2cm do 4m viz datasheet [Senzor HC-SR04](https://vutbr-my.sharepoint.com/personal/xzbori15_vutbr_cz/Documents/Soubory%20z%20chatu%20aplikace%20Microsoft%20Teams/HCSR04.pdf)
 ![Funkce senzoru (bez překážky)](https://github.com/Filip-ZL/Digital-electronics-2/blob/master/Labs/Project/project/images/HC-SR04-Ultrasonic-Sensor-Working-Echo-when-no-Obstacle.gif)\
 *Obr.3 Funkce senzoru bez překážky [1]*\
 ![Funkce senzoru (s překážkou)](https://github.com/Filip-ZL/Digital-electronics-2/blob/master/Labs/Project/project/images/HC-SR04-Ultrasonic-Sensor-Working-Echo-reflected-from-Obstacle.gif)\
 *Obr.4 Funkce senzoru s překážkou [1]*
 
 
 ### Display (HD44780)
 K řízení obrazu je využívána knihovna od [Peter Fleury](http://www.peterfleury.epizy.com/avr-software.html?i=1).
 
 
 ### Posuvný registr (74HC595)
 Je používán k řízení indikátoru vybuzení. Kód je obdobný s kódem vytvořeným v [Lab.5](https://github.com/Filip-ZL/Digital-electronics-2/tree/master/Labs/05-segments/segments/segments).
 
 
 ### MUX
 Funguje jako sběrnice (přímá data vždy jen z jednoho senzoru). je řízený mikrokontrolérem, v tomto případě *ATmega328p*
 
 
 ### LED Bar
 Byl použit LED Bar s 8 segmenty.
 
 ### Simulace
 1. [Simulace](https://youtu.be/EFfpQ9luzMA) předního a zadního sensoru v programu SimulIDE (v. 0.4.13)
 2. [Simulace](https://youtu.be/Ew5TH7cMuqA) správné funkčnosti sensoru HC-SR04
 
 
 
 
 
 
 
 
 
 
 ### Reference
 [1]
 How HC-SR04 Ultrasonic Sensor Works & Interface It With Arduino. Last Minute Engineers [online]. Neuvedeno: Neuvedeno, Neuvedeno [cit. 2020-12-14]. Dostupné z: https://lastminuteengineers.com/arduino-sr04-ultrasonic-sensor-tutorial/
