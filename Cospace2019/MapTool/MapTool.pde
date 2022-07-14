import java.math.*;
PImage bg; 

int boxsize = 10;
int cols, rows;
color[][] colors;
char[][] data;

 
void setup() {
  size(1000, 750);
  String imageName = "map2PRO.jpeg";
  bg = loadImage(imageName);
  cols = width/boxsize;
  rows = height/boxsize;
  colors = new color[cols][rows];
  data = new char[rows][cols];
  for (int i=0; i<cols; i++) {
    for (int j=0; j<rows; j++) {
      colors[i][j] = color(255,100);
      data[j][i] = '0';
    }
  }
}

char letter; 
int keyIndex = -1; 
void keyPressed(){
  switch(key){
    case('q'):
    keyIndex = 1;
    letter = 'q';
    break;
    case('w'):
    keyIndex = 2; 
    letter = 'w';
    break;
    case('e'):
    keyIndex = 3; 
    letter = 'e';
    break;
    case('p'):
    keyIndex = 4; 
    letter = 'p';
    break;
  }
}

void keyReleased(){
  letter = ' ';
}
int count = 0;
 
void printData(){
    for (int i=0; i<cols; i++){
    for (int j=0; j<rows; j++){
      print(data[j][i]+ ",");
    }
    println();
    }
}
 
void draw() {
  background(bg);
  
  if(letter == 'p' && mousePressed ){
    printData();
  }
  for (int i=0; i<cols; i++) {
    for (int j=0; j<rows; j++) {
      int x = i*boxsize;
      int y = j*boxsize;
      if (mouseX > x && mouseX < (x + boxsize) && mouseY > y && mouseY < (y + boxsize)) {
        if (mousePressed && letter == 'q'){
          colors[i][j] = color(255,0,0,150);
          data[j][i] = 'q';
        } else if (mousePressed && letter == 'w'){
          colors[i][j] = color(255, 255, 0,150);
          data[j][i] = 'w';
        } else if(mousePressed && letter == 'e'){
          colors[i][j] = color(10,255,20,150);
          data[j][i] = 'e';
        }else{
        colors[i][j] = colors[i][j];
      }
      }
      fill(colors[i][j],150);
      rect(x, y, boxsize, boxsize);
    }
  }
}
