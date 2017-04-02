# Exploring using external web interfaces for your Arduino

I think it's amazing that [$4 ESP8266 boards](http://s.click.aliexpress.com/e/uzFUnIe) can host webpages, but actually writing the webpage within your sketch can be very frustrating! In these examples I'm going to look at some different ways of moving the development away from the Arduino.

The server code for these examples can be found [here](https://github.com/witnessmenow/external-web-interfaces-arduino)

## Redirect and Ajax example

1) End user requests page from ESP8266
2) ESP8266 responds with a page that will redirect users browser to external page
3) Params will be sent to the external page including the IP address of the ESP8266
4) The webpage will repeatedly make ajax (background) requests to the data endpoint of the ESP8266 and display the response on the page

Main advantage of this is how simple it is, it only uses HTML and javascript (it will run on any webserver). You can also make cosmetic changes to the web interface without changing the code on the ESP8266

Biggest disadvantage is that even though the website is hosted externally, the user still needs to be on the same internal network as the ESP8266
