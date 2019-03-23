import ddf.minim.*;
import ddf.minim.analysis.*;
import ddf.minim.effects.*;
import ddf.minim.signals.*;
import ddf.minim.spi.*;
import ddf.minim.ugens.*;

Minim minim;

AudioPlayer song;

void setup(){
  
  
  
  minim = new Minim(this);
  song = minim.loadFile("yodel.mp3");
  song.play();
  print("{");
}

void draw(){

}


void keyPressed(){
  print("{");
  print(millis());
  
  if (key=='a' || key=='u')
  print(",1");
  
  else if (key=='z' || key=='i')
  print(",2");
  
  else if (key=='e' || key=='o')
  print(",3");
  
  else if (key=='r' || key=='p')
  print(",4");
  
  
  if (key=='a' || key=='z' || key=='e' || key=='r')
  print(",1},");
  else
  print(",2},");
  
}
  
  
  
  
  
  
  
  
  
