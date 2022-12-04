#include "Output.h"
#include <cmath>

Output::Output()
{
	//Initialize user interface parameters
	UI.InterfaceMode = MODE_DRAW;

	UI.width = 1250;
	UI.height = 650;
	UI.wx = 5;
	UI.wy = 5;


	UI.StatusBarHeight = 50;
	UI.ToolBarHeight = 50;
	UI.MenuItemWidth = 60;

	UI.DrawColor = BLUE;	//Drawing color
	UI.FillColor = GREEN;	//Filling color
	UI.MsgColor = RED;		//Messages color
	UI.BkGrndColor = LIGHTGOLDENRODYELLOW;	//Background color
	UI.HighlightColor = MAGENTA;	//This color should NOT be used to draw figures. use if for highlight only
	UI.StatusBarColor = TURQUOISE;
	UI.ToolBarColor = WHITE;
	UI.PenWidth = 3;	//width of the figures frames


	//Create the output window
	pWind = CreateWind(UI.width, UI.height, UI.wx, UI.wy);
	//Change the title
	pWind->ChangeTitle("Paint for Kids - Programming Techniques Project");

	CreateDrawToolBar();
	CreateStatusBar();
}


Input* Output::CreateInput() const
{
	Input* pIn = new Input(pWind);
	return pIn;
}

//======================================================================================//
//								Interface Functions										//
//======================================================================================//

window* Output::CreateWind(int w, int h, int x, int y) const
{
	window* pW = new window(w, h, x, y);
	pW->SetBrush(UI.BkGrndColor);
	pW->SetPen(UI.BkGrndColor, 1);
	pW->DrawRectangle(0, UI.ToolBarHeight, w, h);
	return pW;
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::CreateStatusBar() const
{
	pWind->SetPen(UI.StatusBarColor, 1);
	pWind->SetBrush(UI.StatusBarColor);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::ClearStatusBar() const
{
	//Clear Status bar by drawing a filled white rectangle
	pWind->SetPen(UI.StatusBarColor, 1);
	pWind->SetBrush(UI.StatusBarColor);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
}
void Output::ClearToolBar() const
{
	pWind->SetPen(UI.ToolBarColor, 1);
	pWind->SetBrush(UI.ToolBarColor);
	pWind->DrawRectangle(0, 0, UI.width, UI.ToolBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::CreateDrawToolBar() const
{
	UI.InterfaceMode = MODE_DRAW;
	//You can draw the tool bar icons in any way you want.
	//Below is one possible way

	//First prepare List of images for each menu item
	//To control the order of these images in the menu, 
	//reoder them in UI_Info.h ==> enum DrawMenuItem
	string MenuItemImages[DRAW_ITM_COUNT];
	MenuItemImages[ITM_RECT] = "images\\MenuItems\\Menu_Rect.jpg";
	MenuItemImages[ITM_Tri] = "images\\MenuItems\\Menu_Tri.jpg";
	MenuItemImages[ITM_Square] = "images\\MenuItems\\Menu_Square.jpg";
	MenuItemImages[ITM_Circle] = "images\\MenuItems\\Menu_Circ.jpg";
	MenuItemImages[ITM_Hexagon] = "images\\MenuItems\\Menu_Hexagon.jpg";
	MenuItemImages[SELECT_ONE] = "images\\MenuItems\\Menu_Select.jpg";
	MenuItemImages[CHANGE_COLOR] = "images\\MenuItems\\Menu_Change_Color.jpg";
	MenuItemImages[ITM_DELETE] = "images\\MenuItems\\Menu_Delete.jpg";
	MenuItemImages[UNDO] = "images\\MenuItems\\Menu_Undo.jpg";
	MenuItemImages[REDO] = "images\\MenuItems\\Menu_Redo.jpg";
	MenuItemImages[MOVE] = "images\\MenuItems\\Menu_Move.jpg";
	MenuItemImages[CLEAR_ALL] = "images\\MenuItems\\Menu_Clear_All.jpg";
	MenuItemImages[START_RECORD] = "images\\MenuItems\\Menu_Start_Record.jpg";
	MenuItemImages[STOP_RECORD] = "images\\MenuItems\\Menu_Stop_Record.jpg";
	MenuItemImages[PLAY_RECORD] = "images\\MenuItems\\Menu_Play_Record.jpg";
	MenuItemImages[SAVE] = "images\\MenuItems\\Menu_Save.jpg";
	MenuItemImages[LOAD] = "images\\MenuItems\\Menu_Load.jpg";
	MenuItemImages[SWITCH_TO_PLAY_MODE] = "images\\MenuItems\\Menu_To_Play.jpg";
	MenuItemImages[ITM_EXIT] = "images\\MenuItems\\Menu_Exit.jpg";


	//TODO: Prepare images for each menu item and add it to the list

	//Draw menu item one image at a time
	for (int i = 0; i < DRAW_ITM_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], i * (UI.MenuItemWidth + 4), 0, UI.MenuItemWidth, UI.ToolBarHeight);



	//Draw a line under the toolbar
	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);

}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::CreatePlayToolBar() const
{

	UI.InterfaceMode = MODE_PLAY;
	ClearToolBar();
	string MenuItemImages[PLAY_ITM_COUNT];
	MenuItemImages[FIGURE_TYPE] = "images\\MenuItems\\Menu_Hide_Figure.jpg";
	MenuItemImages[FIGURE_FILL_COLOR] = "images\\MenuItems\\Menu_Hide_Color.jpg";
	MenuItemImages[FIGURE_TYPE_COLOR] = "images\\MenuItems\\Menu_Hide_Figure_Color.jpg";
	MenuItemImages[SWITCH_TO_DRAW_MODE] = "images\\MenuItems\\Menu_To_Draw.jpg";
	MenuItemImages[PLAY_EXIT] = "images\\MenuItems\\Menu_Exit.jpg";


	for (int i = 0; i < PLAY_ITM_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], i * (UI.MenuItemWidth + 4), 0, UI.MenuItemWidth, UI.ToolBarHeight);


	//Draw a line under the toolbar
	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);
	///TODO: write code to create Play mode menu
}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::ClearDrawArea() const
{
	pWind->SetPen(UI.BkGrndColor, 1);
	pWind->SetBrush(UI.BkGrndColor);
	pWind->DrawRectangle(0, UI.ToolBarHeight, UI.width, UI.height - UI.StatusBarHeight);

}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::PrintMessage(string msg) const	//Prints a message on status bar
{
	ClearStatusBar();	//First clear the status bar

	pWind->SetPen(UI.MsgColor, 50);
	pWind->SetFont(20, BOLD, BY_NAME, "Arial");
	pWind->DrawString(10, UI.height - (int)(UI.StatusBarHeight / 1.5), msg);
}
//////////////////////////////////////////////////////////////////////////////////////////

color Output::getCrntDrawColor() const	//get current drawing color
{
	return UI.DrawColor;
}
//////////////////////////////////////////////////////////////////////////////////////////

color Output::getCrntFillColor() const	//get current filling color
{
	return UI.FillColor;
}
//////////////////////////////////////////////////////////////////////////////////////////

int Output::getCrntPenWidth() const		//get current pen width
{
	return UI.PenWidth;
}

//======================================================================================//
//								Figures Drawing Functions								//
//======================================================================================//

void Output::DrawRect(Point P1, Point P2, GfxInfo RectGfxInfo, bool selected) const
{
	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = RectGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, 1);
	drawstyle style;
	if (RectGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(RectGfxInfo.FillClr);
	}
	else
		style = FRAME;


	pWind->DrawRectangle(P1.x, P1.y, P2.x, P2.y, style);

}
void Output::DrawTri(Point P1, Point P2, Point P3, GfxInfo TriGfxInfo, bool selected) const
{
	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = TriGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, 1);
	drawstyle style;
	if (TriGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(TriGfxInfo.FillClr);
	}
	else
		style = FRAME;

	pWind->DrawTriangle(P1.x, P1.y, P2.x, P2.y, P3.x, P3.y, style);

}

void Output::DrawSquare(Point P1, GfxInfo SquareGfxInfo, bool selected) const
{
	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = SquareGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, 1);
	drawstyle style;
	if (SquareGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(SquareGfxInfo.FillClr);
	}
	else
		style = FRAME;


	pWind->DrawRectangle(P1.x - 100, P1.y - 100, P1.x + 100, P1.y + 100, style);

}
void Output::DrawCircle(Point P1, Point P2, GfxInfo CircleGfxInfo, bool selected) const
{
	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = CircleGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, 1);
	drawstyle style;
	if (CircleGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(CircleGfxInfo.FillClr);
	}
	else
		style = FRAME;
	const int Radius = sqrt(pow(P1.x - P2.x, 2) + pow(P1.y - P2.y, 2));

	pWind->DrawCircle(P1.x, P1.y, Radius, style);

}
void Output::DrawHexagon(Point P1, GfxInfo HexagonGfxInfo, bool selected) const
{
	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = HexagonGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, 1);
	drawstyle style;
	if (HexagonGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(HexagonGfxInfo.FillClr);
	}
	else
		style = FRAME;
	int* ix = new int[6];
	int* iy = new int[6];
	ix[0] = P1.x - 50;  	iy[0] = P1.y - (50 * sqrt(3));
	ix[1] = P1.x + 50;      iy[1] = P1.y - (50 * sqrt(3));
	ix[2] = P1.x + 100;     iy[2] = P1.y;
	ix[3] = P1.x + 50;      iy[3] = P1.y + (50 * sqrt(3));
	ix[4] = P1.x - 50;      iy[4] = P1.y + (50 * sqrt(3));
	ix[5] = P1.x - 100;     iy[5] = P1.y;
	pWind->DrawPolygon(ix, iy, 6, style);
	delete[] ix;
	delete[] iy;
	//	pWind->DrawLine(P1.x-50, P1.y-(50*sqrt(3)),P1.x+50, P1.y-(50*sqrt(3)), style);
	//	pWind->DrawLine(P1.x+50, P1.y-(50*sqrt(3)),P1.x+100, P1.y,style);
	//pWind->DrawLine( P1.x+100, P1.y, P1.x+50, P1.y+(50*sqrt(3)), style);
	//pWind->DrawLine( P1.x+50, P1.y+(50*sqrt(3)) ,P1.x-50, P1.y+(50*sqrt(3)),style);
	//pWind->DrawLine(P1.x-50, P1.y+(50*sqrt(3)),P1.x-100, P1.y, style);
	//pWind->DrawLine(P1.x-100, P1.y,P1.x-50, P1.y-(50*sqrt(3)), style);
	//  pWind->DrawRectangle(P1.x-50, P1.y-(50*sqrt(3)),P1.x+50, P1.y+(50*sqrt(3)), style);
	//	pWind->DrawTriangle(P1.x+50, P1.y-(50*sqrt(3)), P1.x+100, P1.y, P1.x+50, P1.y+(50*sqrt(3)),style);
	//	pWind->DrawTriangle(P1.x-50, P1.y+(50*sqrt(3)), P1.x-100, P1.y, P1.x-50, P1.y-(50*sqrt(3)),style);
}


Output::~Output()
{
	delete pWind;
}

