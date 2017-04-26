![Reis](Reis/assets/Reis-logo-small.png)  
# Reis  
  
**Reis** is a cross-platform 2D game engine writen in C++/SDL.  
  
Refactoring code since *February*, 2016.  
  
See the [Wiki](https://github.com/marcelomesmo/Reis/wiki) for full documentation, examples and other information.  
Doxygen available [here](http://marcelomesmo.github.io/Reis-doxygen/html/index.html).  
Download most recent Lib version [here](https://www.dropbox.com/s/f3foxri3ktqql3z/Reis-lib-v1.0.rar?dl=0).  
  
Current version 0.9.0 - April, 2017.  
  
Refactoring Journal:

07/02/2016  
Added Game and GameState classes.  
Added Graphics.  
Added Font to Graphics.  
Added Color to Graphics.  
Added Transition.  
Added FadeOut to Transition.  
Added FadeIn to Transition.  
Added Timer.  
  
10/02/2016  
Added Input.  
Added keyboard support into Input.  
Added mouse support into Input.  
  
14/02/2016  
Added controller support into Input.  
  
16/02/2016  
Added multiple controller support.  
Changed name from Raiz to **Reis**.  
Added [doxygen](http://marcelomesmo.github.io/Reis-doxygen/html/index.html) and icon.  

23/02/2016  
Created [Wiki](https://github.com/marcelomesmo/Reis/wiki).  
Added Install Guide to Wiki.  
Added How to Use - Create Game to Wiki.  
  
*Decided on making smaller but faster pushes instead of big but slow ones*  
  
07/03/2016  
Changed class name from GameState to Scene.  
Added Sprite to Graphics.  
Added SpriteSheet to Graphics.  
Changed a lot of .init()/.load() to .create().  
Changed a lot of .free() to .end().  
Added ColorManager to Graphics.  
Added print key to string functionality to Input.  
  
Added How to Use - Scene to Wiki.  
Added example images to Wiki tutorials.  
  
*Took back on making smaller but faster pushes due to lack of time. Making bigger slow pushes again*  
  
20/03/2016  
Added Animation to Graphics.  
Added XML support to SpriteSheet.  
Added MuSSEXmlParser to Data.  
Changed Sprite creation.  
Added anchor support to Sprite.  
  
13/03/2017
Renamed Timer to Clock.  
Added Resouce to Resources.  
Changed Sprite, Animation and SpriteSheet inheritance.  
Added ResouceHolder to Resources.  
Added ResouceManager to Resources.  
Added XML support to Resources.  
  
24/04/2017
Added color key support to MusseXMLParser.  
  
26/04/2017  
Added anchor point support to MusseXMLParser.  
Revised Error messages.  
Removed Debug messages.  
  
  </br>
Feel free to make contributions.  
If you encounter any bugs, please send me an email.  

Authors’ contact:  
https://marcelomesmo.github.io  
marcelo.barbosa (at) ifrn.edu.br   
  
Reis is distributed under the terms and conditions of the [zlib/png license](http://zlib.net/zlib_license.html).
