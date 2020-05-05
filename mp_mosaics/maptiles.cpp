/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */

	int rows = theSource.getRows();
	int cols = theSource.getColumns();

	if(rows == 0 || cols == 0){
		return NULL;
	}


	MosaicCanvas* output = new MosaicCanvas(rows, cols);
	vector<Point<3>> newPoints;
	map<Point<3>, TileImage*> tiles_map;

	for(unsigned int i = 0; i < theTiles.size(); i++){
		LUVAPixel tmp = theTiles[i].getAverageColor();
		Point<3> newPoint = convertToXYZ(tmp);
		newPoints.push_back(newPoint);
		tiles_map[newPoint] = &theTiles[i];
	}	

	KDTree<3>* kdTree = new KDTree<3>(newPoints);

	for(int j = 0 ; j < rows; j++){
		for(int k = 0; k < cols; k++){
			Point<3> target = convertToXYZ(theSource.getRegionColor(j,k));
			Point<3> nearest = kdTree->findNearestNeighbor(target);

			output->setTile(j,k, tiles_map[nearest]); 


		}
	}
 
    return output;
}

//void MosaicCanvas::setTile(int row, int column, TileImage* i)
//LUVAPixel getAverageColor() const { return averageColor_; }
