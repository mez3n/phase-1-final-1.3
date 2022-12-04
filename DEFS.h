#ifndef DEFS_H
#define DEFS_H

#include "CMUgraphicsLib\CMUgraphics.h"

//This file contains some global constants and definitions to be used in the project.
enum ActionType //The actions supported (you can add more if needed)
{
	DRAW_RECT,//Draw Rectangle
	DRAW_Tri,
	DRAW_Square,
	DRAW_Circle,
	DRAW_Hexagon,
	EXIT,			//Exit
	TO_DRAW,		//Switch interface to Draw mode
	TO_PLAY,		//Switch interface to Play mode
	EMPTY,			//A click on empty place in the toolbar
	DRAWING_AREA,	//A click on the drawing area
	STATUS ,//A click on the status bar
	FIGURE_TYPE_ACT,
	FIGURE_FILL_COLOR_ACT,
	FIGURE_TYPE_COLOR_ACT,
	SELECT_ONE_ACT,
	CHANGE_COLOR_ACT,
	DELETE_ACT,
	MOVE_ACT,
	UNDO_ACT,
	REDO_ACT,
	CLEAR_ALL_ACT,
	START_RECORD_ACT,
	STOP_RECORD_ACT,
	PLAY_RECORD_ACT,
	SAVE_ACT,
	LOAD_ACT,
	/*MOVE_DRAG_ACT,
	RESIZE_ACT*/
	///TODO: Add the other action types of the two modes
};

struct Point	//To be used for figures points
{ int x,y; };

struct GfxInfo	//Graphical info of each figure (you may add more members)
{
	color DrawClr;	//Draw color of the figure
	color FillClr;	//Fill color of the figure
	bool isFilled;	//Figure Filled or not
	int BorderWdth;	//Width of figure borders

};

#endif