////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.h 
////////////////////////////////////////////////////////////////////////////////
#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "d3dclass.h"
#include "cameraclass.h"
#include "modelclass.h"
#include "lightshaderclass.h"
#include "lightclass.h"
#include "inputclass.h"


/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = true;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;


////////////////////////////////////////////////////////////////////////////////
// Class name: GraphicsClass
////////////////////////////////////////////////////////////////////////////////
class GraphicsClass
{
public:

	GraphicsClass(InputClass *m_iinput);
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame();

private:
	bool Render(float);

private:
	D3DClass* m_D3D;
	CameraClass* m_Camera;
	ModelClass* m_Human_Head;
	ModelClass* m_Human_Body;
	ModelClass* m_Human_Left_Leg;
	ModelClass* m_Human_Left_Arm;
	ModelClass* m_Human_Right_Leg;
	ModelClass* m_Human_Right_Arm;
	//기존 m_UpDownObstacle 수정
	ModelClass* m_Map;
	///////////////////////////////////////추가 시작//////
	ModelClass* m_Shoot_bullet;
	ModelClass* m_Shoot_bullet_1stMove;
	ModelClass* m_Shoot_bullet_2ndMove;
	/////////////////////////////////////////////////////0621 지명근 추가 시작//////////
	ModelClass* m_Shoot_bullet_3rdMove;
	ModelClass* m_Shoot_bullet_rightmap_no1;
	ModelClass* m_Shoot_bullet_rightmap_no2;
	ModelClass* m_Shoot_bullet_rightmap_no3;
	ModelClass* m_Shoot_bullet_rightmap_no4;
	ModelClass* m_Shoot_bullet_rightmap_no5;
	ModelClass* m_Shoot_bullet_leftmap_no1;
	ModelClass* m_Shoot_bullet_leftmap_no2;
	ModelClass* m_Shoot_bullet_leftmap_no3;
	ModelClass* m_Shoot_bullet_leftmap_no4;
	ModelClass* m_Shoot_bullet_leftmap_no5;
	ModelClass* m_Shoot_bullet_leftmap_no6;
	ModelClass* m_Shoot_bullet_leftmap_no7;
	ModelClass* m_Map_LeftFinish;
	ModelClass* m_Map_RightFinish;
	/////////////////////////////////////////////////////0621 지명근 추가 끝//////////
	ModelClass* m_Map_1stMove;
	ModelClass* m_Map_2ndMove;
	///////////////////////////////////////추가   끝//////

	///////////////////////////////////0617 박민 추가 시작/////////////
	ModelClass* m_UpDownObstacle[9];
	ModelClass* m_RotObstacle[24];
	ModelClass* m_Map2;
	ModelClass* m_Map3;
	ModelClass* m_DynamicBoard[4];

	ModelClass* m_Stage2Map[3];
	ModelClass* m_Stage2background[4];
	ModelClass* m_AvoidObstacle[7];
	ModelClass* m_BridgeObstacle[10];
	ModelClass* m_BBD;

	ModelClass* m_menu;
	ModelClass* m_select[4];
	ModelClass* m_Stage1background;
	///////////////////////////////////0617 박민 추가 끝/////////////
	///////////////////////////////////0620 김형륙 추가 시작/////////////
	ModelClass* m_Time;
	ModelClass* m_RunGaze;
	ModelClass* m_RunControl;
	ModelClass* m_HitCombo;
	ModelClass* m_UpDownObstaclee;
	///////////////////////////////////0620 김형륙 추가 끝/////////////
	bool checkJump;
	LightShaderClass* m_LightShader;
	InputClass *m_input;
	LightClass* m_Light;
	float x;
	float left;
	float right;



};

#endif