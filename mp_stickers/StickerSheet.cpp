#include "StickerSheet.h"
#include <string>
#include <cmath>

StickerSheet::StickerSheet(const Image &picture, unsigned max){
  max_num = max;
  scene = new Image*[max_num];
  index = new unsigned[max_num];
  x_cor = new unsigned[max_num];
  y_cor = new unsigned[max_num];
  for (unsigned i = 0; i < max_num;i++){
    scene[i] = NULL;
    index[i] = 0;
    x_cor[i] = 0;
    y_cor[i] = 0;
  }
  base_image = picture; //deep copy
  cur_sticker = 0;
}

StickerSheet::~StickerSheet(){  //destructor
  this->clear();
}

StickerSheet::StickerSheet(const StickerSheet &other){ //copy constructor
  this->copy(other);
}

const StickerSheet& StickerSheet::operator=(const StickerSheet &other){
  clear();
  this->copy(other);
  return *this;
}

void StickerSheet::changeMaxStickers(unsigned max){
    if(max_num == max){return;}

    if(max < max_num){  //if max is less,  free the rest;
      for(unsigned k = max; k < max_num;k++){
        if(scene[k] != NULL){
          //delete scene[k];   //memory leak cause #1
          removeSticker(k);
        }
      }
      max_num = max;
    }

    if(max > max_num){ // if max is more, allocate new memory and make original point to it after clearing
      
      Image** scene_temp = new Image *[max];
      unsigned *index_temp = new unsigned[max];
      unsigned *x_cor_temp = new unsigned[max];
      unsigned *y_cor_temp = new unsigned[max];
      
      for (unsigned q = 0; q < max;q++){
        scene_temp[q] = NULL;
        index_temp[q] = 0;
        x_cor_temp[q] = 0;
        y_cor_temp[q] = 0;
      }

      unsigned checknum = cur_sticker;
      for(unsigned i = 0; i < max_num; i++){       
        if(scene[i] != NULL){
          scene_temp[i] = new Image(*scene[i]);
          checknum--; 
        }
        index_temp[i]=index[i];
        x_cor_temp[i]=x_cor[i];
        y_cor_temp[i]=y_cor[i];
      } 

      this->clear();

      max_num = max;
      scene = scene_temp;
      index = index_temp;
      x_cor = x_cor_temp;
      y_cor = y_cor_temp;
           
      scene_temp = NULL;
      index_temp=NULL;
      x_cor_temp=NULL;
      y_cor_temp=NULL;
    }  
}

int StickerSheet::addSticker(Image & sticker, unsigned x, unsigned y){
  if(cur_sticker < max_num){
    for(unsigned i = 0 ; i < max_num; i++){
      if(scene[i] == NULL){
        scene[i] = new Image(sticker);
        index[i] = i+1;
        x_cor[i] = x;
        y_cor[i] = y;
        cur_sticker++;
        return int(i);
      }
    }
  }
  return -1;
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y){
  if(scene[index] == NULL || index >= max_num){
    return false;
  }

  x_cor[index] = x;
  y_cor[index] = y;
  return true;
}

void StickerSheet::removeSticker(unsigned index){
    delete scene[index];  //memory leak fix #1
    scene[index] = NULL;
    x_cor[index] = 0;
    y_cor[index] = 0;
    this->index[index] = 0;
    cur_sticker--;
}

Image* StickerSheet::getSticker(unsigned index){
  if(scene[index] == NULL){
    return NULL;
  }
  return scene[index];
}

Image StickerSheet::render() const{
  Image result_image; // = base_image;
  result_image = this->base_image;

  unsigned width = result_image.width();
  unsigned height = result_image.height();
  unsigned newx= width;
  unsigned newy= height;

  for(unsigned p=0;p<max_num;p++){
    if(scene[p]!=NULL){
      newx=fmax(newx,(scene[p]->width()+x_cor[p]));
      newy=fmax(newy,(scene[p]->height()+y_cor[p]));
    }
  }

  result_image.resize(newx,newy);
  for(unsigned i =0;i<max_num;i++){
    if(scene[i] != NULL){
      for(unsigned j=0;j<scene[i]->width();j++){
          for(unsigned k =0; k< scene[i]->height();k++){
            cs225::HSLAPixel & pixel1 = result_image.getPixel(x_cor[i]+j, y_cor[i]+k);
            cs225::HSLAPixel & pixel2 = scene[i]->getPixel(j, k);
            if(pixel2.a !=0){
              pixel1 = pixel2;
            }
          }
        }
      }
   }
  return result_image;
}

void StickerSheet::copy(const StickerSheet &that){
  max_num = that.max_num;
  base_image = that.base_image;
  cur_sticker = that.cur_sticker;
  
  scene = new Image *[max_num];
  x_cor = new unsigned[max_num];
  y_cor = new unsigned[max_num];
  index = new unsigned[max_num];

  for (unsigned i = 0; i < max_num;i++){
    scene[i] = NULL;
    x_cor[i] = 0;
    y_cor[i] = 0;
    index[i] = 0;
  }
  
  for(unsigned j=0; j < max_num;j++){
     if(that.scene[j] != NULL){
          scene[j] = new Image(*(that.scene[j]));
     }    
    index[j] = that.index[j];
    x_cor[j] = that.x_cor[j];
    y_cor[j] = that.y_cor[j];
  }
}

void StickerSheet::clear(){
  for(unsigned i = 0; i<max_num; i++){
    if(scene[i] != NULL){
      delete scene[i];
      scene[i] =NULL;
    }
  }
  delete[] scene;  //memory leak fix 2
  delete[] index;
  delete[] x_cor;
  delete[] y_cor;
  scene = NULL;    //memory leak fix 2
  index = NULL;
  x_cor = NULL;
  y_cor = NULL;
}
