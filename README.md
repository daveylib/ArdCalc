# ArdCalc - Arduino Calculator

Simple calculator with four basic operations based on Arduino Uno.

<img src="./Images/ardcalc0.jpg" />

<h2>What you need to make it?</h2>

<ul>
  <li>Arduino board (ATmega328)</li><br/>
  
  <li>LCD Screen (compatible with Hitachi HD44780 driver)</li>
  <li>10k ohm potentiometer</li>
  <li>220 ohm resistor</li><br/>

  <li>PCF8574 expander</li><br/>
  
  <li>15x pushbuttons</li>
  <li>7x 10K ohm resistors</li>
</ul>

<h2>Wiring</h2>

<img src="./Images/fritzing.png" />

<h2>How it works?</h2>

<img src="./Images/ardcalc1.jpg" width="210" height="150" />
<img src="./Images/ardcalc2.jpg" width="210" height="150" />
<img src="./Images/ardcalc3.jpg" width="210" height="150" />
<img src="./Images/ardcalc4.jpg" width="210" height="150" />

In the beginning we see „Arduino Calculator”. To start typing the first number, press „OK”.<br/>
After typing the number, choose one of the four basic operations mentioned below:
<ul>
<li>` + ` - addition</li>
<li>` - ` - subtraction</li>
<li>` * ` - multiplication</li>
<li>` / ` - division</li>
</ul>

After typing the second number, press „OK” to show the result.<br/>
If you want to reset the calculator, press "OK" again. <br/><br/>


In order for ArdCalc to work correctly, I had to add some limitations:

1. If one of the numbers entered is greater than 999999, you will see "error” on the display.<br/>
2. If you try to divide by zero, you will see „inf” ( „infinity” ) on the display.
