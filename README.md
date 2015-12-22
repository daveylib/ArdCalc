# ArdCalc - Arduino Calculator

Simple calculator with four basic operations based on Arduino Uno.

<img src="http://oi67.tinypic.com/4sinme.jpg" />

<h2>What you need to make it?</h2>

<ul>
  <li>Arduino board</li><br/>
  
  <li>LCD Screen (compatible with Hitachi HD44780 driver)</li>
  <li>10k ohm potentiometer</li>
  <li>220 ohm resistor</li><br/>

  <li>PCF8574 expander</li><br/>
  
  <li>15 pushbuttons</li>
  <li>7 10K ohm resistors</li>
</ul>

<h2>Wiring</h2>

<img src="http://oi64.tinypic.com/2h4du9y.jpg" />

<h2>Demonstration</h2>

<img src="http://oi66.tinypic.com/20ktb84.jpg" width="210" height="150" />
<img src="http://oi67.tinypic.com/2ilm2c5.jpg" width="210" height="150" />
<img src="http://oi68.tinypic.com/nyxnad.jpg" width="210" height="150" />
<img src="http://oi64.tinypic.com/b3kf0w.jpg" width="210" height="150" />

<h2>How it works?</h2>

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


