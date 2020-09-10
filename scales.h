//Diatonic Modes

//the root note is played at 3:1 ratio across two octaves
int scales[7][18] = {
  //Ionian (Major) Scale = whole, whole, half, whole, whole, whole, half
  {0, 0, 0, 2, 4, 5, 7, 9, 11, 12, 12, 12, 14, 16, 17, 19, 21, 23},

  // Dorian Scale = whole, half, whole, whole, whole,  half, whole
  {0, 0, 0, 2, 3, 5, 7, 9, 10, 12, 12, 12, 14, 15, 17, 19, 21, 22},

  // Phrygian Scale = half, whole, whole, whole, half, whole, whole
  {0, 0, 0, 1, 3, 5, 7, 8, 10, 12, 12, 12, 13, 15, 17, 19, 20, 22},

  // Lydian Scale = whole, whole, whole, half, whole, whole, half
  {0, 0, 0, 2, 4, 6, 7, 9, 11, 12, 12, 12, 14, 16, 18, 19, 21, 23},

  // Mixolydian Scale = whole, whole, half, whole, whole, half, whole
  {0, 0, 0, 2, 4, 5, 7, 9, 10, 12, 12, 12, 14, 16, 17, 19, 21, 22},

  // Aeolian (Minor) Scale = whole, half, whole, whole, half, whole, whole
  {0, 0, 0, 2, 3, 5, 7, 8, 10, 12, 12, 12, 14, 15, 17, 19, 20, 22},

  // Locrian Scale = half, whole, whole, half, whole, whole, whole
  {0, 0, 0, 1, 3, 5, 6, 8, 10, 12, 12, 12, 13, 15, 17, 18, 20, 22}

};

//Determine how many scales are in the array.  
//This will allow us to map a sensor to it. These are
//the rows of the scales[][] matrix. 
int scalesArrayLength = sizeof(scales)/sizeof(scales[0]);

//Determine how many notes are in the array.  
//This will allow us to map a sensor to it. These are
//the columns of the scales[][] matrix. 
int diatonicArrayLength = sizeof(scales[0])/sizeof(int); 
