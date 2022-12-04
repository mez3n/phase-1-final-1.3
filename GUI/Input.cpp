#include "Input.h"
#include "Output.h"


Input::Input(window* pW)
{
	pWind = pW; //point to the passed window
}

void Input::GetPointClicked(int& x, int& y) const
{
	pWind->WaitMouseClick(x, y);	//Wait for mouse click
}

string Input::GetSrting(Output* pO) const
{
	string Label;
	char Key;
	while (1)
	{
		pWind->WaitKeyPress(Key);
		if (Key == 27)	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		if (Key == 13)	//ENTER key is pressed
			return Label;
		if ((Key == 8) && (Label.size() >= 1))	//BackSpace is pressed
			Label.resize(Label.size() - 1);
		else
			Label += Key;
		if (pO)
			pO->PrintMessage(Label);
	}
}

//This function reads the position where the user clicks to determine the desired action
ActionType Input::GetUserAction() const
{
	int x, y;
	pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click

	if (UI.InterfaceMode == MODE_DRAW)	//GUI in the DRAW mode
	{
		//[1] If user clicks on the Toolbar
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / (UI.MenuItemWidth+4));
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
			case ITM_RECT: return DRAW_RECT;
			case ITM_Tri: return DRAW_Tri;
			case ITM_Square: return DRAW_Square;
			case ITM_Circle: return DRAW_Circle;
			case ITM_Hexagon: return DRAW_Hexagon;
			case ITM_EXIT: return EXIT;
			case SWITCH_TO_PLAY_MODE:return TO_PLAY;
			case SELECT_ONE:return SELECT_ONE_ACT;
			case CHANGE_COLOR:return CHANGE_COLOR_ACT;
			case ITM_DELETE:return	DELETE_ACT;
			case UNDO:return UNDO_ACT;
			case REDO:return REDO_ACT;
			case MOVE:return MOVE_ACT;
			case CLEAR_ALL:return CLEAR_ALL_ACT;
			case START_RECORD:return START_RECORD_ACT;
			case STOP_RECORD:return STOP_RECORD_ACT;
			case PLAY_RECORD:return PLAY_RECORD_ACT;
			case SAVE:return SAVE_ACT;
			case LOAD:return LOAD_ACT;

			default: return EMPTY;	//A click on empty place in desgin toolbar
			}
		}

	

			//[2] User clicks on the drawing area
			if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
			{
				return DRAWING_AREA;
			}

		//[3] User clicks on the status bar
		return STATUS;
	}
	else	//GUI is in PLAY mode
	{


		//[1] If user clicks on the Toolbar
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / (UI.MenuItemWidth+4));
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
			case PLAY_EXIT: return EXIT;
			case FIGURE_TYPE:return FIGURE_TYPE_ACT;
			case FIGURE_FILL_COLOR:return FIGURE_FILL_COLOR_ACT;
			case FIGURE_TYPE_COLOR:return FIGURE_TYPE_COLOR_ACT;
			case SWITCH_TO_DRAW_MODE:return TO_DRAW;
			default: return EMPTY;	//A click on empty place in desgin toolbar
			}
		}

		//[2] User clicks on the drawing area
		if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			return DRAWING_AREA;
		}

		//[3] User clicks on the status bar
		return STATUS;
		///TODO:
		//perform checks similar to Draw mode checks above
		//and return the correspoding action
		return TO_PLAY;	//just for now. This should be updated
	}

}
/////////////////////////////////

Input::~Input()
{
}
