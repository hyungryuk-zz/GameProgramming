////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "graphicsclass.h"
#include <DirectXMath.h>
#include <math.h>
#include <direct.h>
#include <time.h>
///////////0617 박민 변수 추가 시작////////////////////
float offset[18];
float offset2[8];
float offset3[6];
float stage = 0; 
const float XM_PI = 3.141592654f;
bool isLook1st = true;
float testjumpfloat = 0.0f;   /////////////////////////점프를 누르면 캐릭터의 높이값////
float jumpposition = 0.0f;   /////////////////////////점프해서 최고 높이에 도달했는지를 체크용도////
float jumppress = 0.0f;       /////////////////////////점프키를 누르면 자동으로 체크점프 라는 불리언 변수를 변경시켜주기 위한 용도//
float selecty = 10.0f;
float selectz = 26.5f;
///////////0617 박민 변수 추가 끝///////////////////
GraphicsClass::GraphicsClass(InputClass *m_iinput)
{
	m_D3D = 0;
	m_Camera = 0;
	m_Human_Head = 0;
	m_Human_Body = 0;
	m_Human_Left_Leg = 0;
	m_Human_Left_Arm = 0;
	m_Human_Right_Leg = 0;
	m_Human_Right_Arm = 0;
	

	m_Map = 0;
	m_LightShader = 0;
	m_Light = 0;
	m_input = m_iinput;
	////////////////////////////////초기화 추가 시작  by 지명근//////
	m_Shoot_bullet = 0;
	m_Shoot_bullet_1stMove = 0;
	m_Shoot_bullet_2ndMove = 0;
	m_Map_1stMove = 0;
	m_Map_2ndMove = 0;
	m_UpDownObstaclee = 0;
	////////////////////////////////////0621 지명근 추가시작////////////
	m_Shoot_bullet_rightmap_no1 = 0;
	m_Shoot_bullet_rightmap_no2 = 0;
	m_Shoot_bullet_rightmap_no3 = 0;
	m_Shoot_bullet_rightmap_no4 = 0;
	m_Shoot_bullet_rightmap_no5 = 0;
	m_Shoot_bullet_leftmap_no1 = 0;
	m_Shoot_bullet_leftmap_no2 = 0;
	m_Shoot_bullet_leftmap_no3 = 0;
	m_Shoot_bullet_leftmap_no4 = 0;
	m_Shoot_bullet_leftmap_no5 = 0;
	m_Shoot_bullet_leftmap_no6 = 0;
	m_Shoot_bullet_leftmap_no7 = 0;
	m_Map_LeftFinish = 0;
	m_Map_RightFinish = 0;
	////////////////////////////////////0621 지명근 추가끝////////////
	////////////////////////////////초기화 추가   끝  by 지명근//////
	////////////////////////////////0620 김형륙 추가시작//////////////////
	m_Time = 0;
	m_RunGaze = 0;
	m_RunControl = 0;
	m_HitCombo = 0;
	////////////////////////////////0620 김형륙 추가끝//////////////////
	////////////////////////////////0617 박민 추가//////////////////

	for (int i = 0; i < 9; i++)
		m_UpDownObstacle[i] = 0;

	for (int i = 0; i < 24; i++)
		m_RotObstacle[i] = 0;
	m_Map2 = 0;
	m_Map3 = 0;

	for (int i = 0; i < 4; i++)
		m_DynamicBoard[i] = 0;

	for (int i = 0; i < 3; i++)
		m_Stage2Map[i] = 0;

	for (int i = 0; i < 4; i++)
		m_Stage2background[i] = 0;

	for (int i = 0; i < 7; i++)
		m_AvoidObstacle[i] = 0;

	for (int i = 0; i < 10; i++)
		m_BridgeObstacle[i] = 0;


	m_BBD = 0;
	for (int i = 0; i < 4; i++)
		m_select[i];

	m_Stage1background = 0;

	//////////////////////////////////0617 박민 추가 끝 ///////////////

}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}


GraphicsClass::~GraphicsClass()
{
}


D3DXMATRIX sumAllMovement;
bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;
	checkJump = false;
	x = 0.0f;
	left = 0.0f;
	right = 0.0f;
	D3DXMatrixIdentity(&sumAllMovement);
	// Create the Direct3D object.
	m_D3D = new D3DClass;
	if (!m_D3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}

	// Create the camera object.
	m_Camera = new CameraClass;
	if (!m_Camera)
	{
		return false;
	}

	// Set the initial position of the camera.
	m_Camera->SetPosition(0.0f, 2.0f, -10.0f);



	// Create the model object.



	m_Human_Right_Leg = new ModelClass;
	if (!m_Human_Right_Leg)
	{
		return false;
	}
	m_Map = new ModelClass;
	if (!m_Map)
	{
		return false;
	}
	//////////////////////////////////////////////////2016.06.20 김형륙 추가 시작
	m_RunGaze = new ModelClass;
	if (!m_RunGaze)
	{
		return false;
	}m_HitCombo = new ModelClass;
	if (!m_HitCombo)
	{
		return false;
	}
	m_Time= new ModelClass;
	if (!m_Time)
	{
		return false;
	}
	m_RunControl = new ModelClass;
	if (!m_Time)
	{
		return false;
	}
	m_Shoot_bullet = new ModelClass;
	if (!m_Shoot_bullet)
	{
		return false;
	}
	m_Shoot_bullet_1stMove = new ModelClass;
	if (!m_Shoot_bullet_1stMove)
	{
		return false;
	}
	m_Shoot_bullet_2ndMove = new ModelClass;
	if (!m_Shoot_bullet_2ndMove)
	{
		return false;
	}
	m_Map_1stMove = new ModelClass;
	if (!m_Map_1stMove)
	{
		return false;
	}
	m_Map_2ndMove = new ModelClass;
	if (!m_Map_2ndMove)
	{
		return false;
	}
	//////////////////////////////////////////////////2016.06.20 김형륙 추가 끝
	m_Human_Right_Arm = new ModelClass;
	if (!m_Human_Right_Arm)
	{
		return false;
	}
	m_UpDownObstaclee = new ModelClass;
	if (!m_UpDownObstaclee)
	{
		return false;
	}
	m_Human_Head = new ModelClass;
	if (!m_Human_Head)
	{
		return false;
	}
	m_Human_Left_Leg = new ModelClass;
	if (!m_Human_Left_Leg)
	{
		return false;
	}
	m_Human_Left_Arm = new ModelClass;
	if (!m_Human_Left_Arm)
	{
		return false;
	}

	m_Human_Body = new ModelClass;
	if (!m_Human_Body)
	{
		return false;
	}
	/////////////////////////////////////0617 박민 모델클래스 추가 시작////////////
	for (int i = 0; i < 9; i++)
	{
		m_UpDownObstacle[i] = new ModelClass;
		if (!m_UpDownObstacle[i])
		{
			return false;
		}
	}

	for (int i = 0; i < 24; i++)
	{
		m_RotObstacle[i] = new ModelClass;
		if (!m_RotObstacle[i])
		{
			return false;
		}
	}
	m_Map2 = new ModelClass;
	if (!m_Map2)
	{
		return false;
	}
	m_Map3 = new ModelClass;
	if (!m_Map3)
	{
		return false;
	}
	for (int i = 0; i < 4; i++)
	{
		m_DynamicBoard[i] = new ModelClass;
		if (!m_DynamicBoard[i])
		{
			return false;
		}
	}
	for (int i = 0; i < 3; i++)
	{
		m_Stage2Map[i] = new ModelClass;
		if (!m_Stage2Map[i])
		{
			return false;
		}
	}
	for (int i = 0; i < 4; i++)
	{
		m_Stage2background[i] = new ModelClass;
		if (!m_Stage2background[i])
		{
			return false;
		}
	}

	m_BBD = new ModelClass;
	if (!m_BBD)
	{
		return false;
	}

	for (int i = 0; i < 7; i++)
	{
		m_AvoidObstacle[i] = new ModelClass;
		if (!m_AvoidObstacle[i])
		{
			return false;
		}
	}

	for (int i = 0; i < 10; i++)
	{
		m_BridgeObstacle[i] = new ModelClass;
		if (!m_BridgeObstacle[i])
		{
			return false;
		}
	}


	m_menu = new ModelClass;
	if (!m_menu)
	{
		return false;
	}
	for (int i = 0; i < 4; i++)
	{
		m_select[i] = new ModelClass;
		if (!m_select[i])
		{
			return false;
		}
	}

	m_Stage1background = new ModelClass;
	if (!m_Stage1background)
	{
		return false;
	}
	/////////////////////////////////////0617 박민 모델클래스 추가 끝////////////


	// Initialize the model object.

	//////////////////////////////////////0621 지명근 모델클레스 추가 시작 //////
	m_Shoot_bullet_3rdMove = new ModelClass;
	if (!m_Shoot_bullet_3rdMove)
	{
		return false;
	}
	m_Shoot_bullet_leftmap_no1 = new ModelClass;
	if (!m_Shoot_bullet_leftmap_no1)
	{
		return false;
	}
	m_Shoot_bullet_leftmap_no2 = new ModelClass;
	if (!m_Shoot_bullet_leftmap_no2)
	{
		return false;
	}
	m_Shoot_bullet_leftmap_no3 = new ModelClass;
	if (!m_Shoot_bullet_leftmap_no3)
	{
		return false;
	}
	m_Shoot_bullet_leftmap_no4 = new ModelClass;
	if (!m_Shoot_bullet_leftmap_no4)
	{
		return false;
	}
	m_Shoot_bullet_leftmap_no5 = new ModelClass;
	if (!m_Shoot_bullet_leftmap_no5)
	{
		return false;
	}
	m_Shoot_bullet_leftmap_no6 = new ModelClass;
	if (!m_Shoot_bullet_leftmap_no6)
	{
		return false;
	}
	m_Shoot_bullet_leftmap_no7 = new ModelClass;
	if (!m_Shoot_bullet_leftmap_no7)
	{
		return false;
	}
	m_Shoot_bullet_rightmap_no1 = new ModelClass;
	if (!m_Shoot_bullet_rightmap_no1)
	{
		return false;
	}
	m_Shoot_bullet_rightmap_no2 = new ModelClass;
	if (!m_Shoot_bullet_rightmap_no2)
	{
		return false;
	}
	m_Shoot_bullet_rightmap_no3 = new ModelClass;
	if (!m_Shoot_bullet_rightmap_no3)
	{
		return false;
	}
	m_Shoot_bullet_rightmap_no4 = new ModelClass;
	if (!m_Shoot_bullet_rightmap_no4)
	{
		return false;
	}
	m_Shoot_bullet_rightmap_no5 = new ModelClass;
	if (!m_Shoot_bullet_rightmap_no5)
	{
		return false;
	}
	m_Map_LeftFinish = new ModelClass;
	if (!m_Map_LeftFinish)
	{
		return false;
	}
	m_Map_RightFinish = new ModelClass;
	if (!m_Map_RightFinish)
	{
		return false;
	}
	//////////////////////////////////////0621 지명근 모델클레스 추가 끝 //////
	////////////////////////////////////2016.06.20 김형륙 추가시작
	result = m_RunControl->Initialize(m_D3D->GetDevice(), "../Engine/data/cube.txt", L"../Engine/data/RunControl.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}
	result = m_HitCombo->Initialize(m_D3D->GetDevice(), "../Engine/data/cube.txt", L"../Engine/data/HitCombo.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}
	result = m_RunGaze->Initialize(m_D3D->GetDevice(), "../Engine/data/cube.txt", L"../Engine/data/RunGaze.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}
	result = m_Time->Initialize(m_D3D->GetDevice(), "../Engine/data/cube.txt", L"../Engine/data/Time.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}
	////////////////////////////////////2016.06.20 김형륙 추가끝
	result = m_Shoot_bullet->Initialize(m_D3D->GetDevice(), "../Engine/data/cube.txt", L"../Engine/data/Shoot_bullet.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}
	result = m_Shoot_bullet_1stMove->Initialize(m_D3D->GetDevice(), "../Engine/data/cube.txt", L"../Engine/data/Shoot_bullet.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}
	result = m_Shoot_bullet_2ndMove->Initialize(m_D3D->GetDevice(), "../Engine/data/cube.txt", L"../Engine/data/Shoot_bullet.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}
	result = m_Map_1stMove->Initialize(m_D3D->GetDevice(), "../Engine/data/cube.txt", L"../Engine/data/Map.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}
	result = m_Map_2ndMove->Initialize(m_D3D->GetDevice(), "../Engine/data/cube.txt", L"../Engine/data/Map.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}
	result = m_Map_LeftFinish->Initialize(m_D3D->GetDevice(), "../Engine/data/cube.txt", L"../Engine/data/Map.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}
	result = m_Map_RightFinish->Initialize(m_D3D->GetDevice(), "../Engine/data/cube.txt", L"../Engine/data/Map.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}
	/////////////////////////////////////////////////////////////추가   끝  by 지명근//////
	/////////////////////////////////////////////////////////////0621추가   시작  by 지명근//////
	result = m_Shoot_bullet_3rdMove->Initialize(m_D3D->GetDevice(), "../Engine/data/cube.txt", L"../Engine/data/Shoot_bullet.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}
	result = m_Shoot_bullet_leftmap_no1->Initialize(m_D3D->GetDevice(), "../Engine/data/cube.txt", L"../Engine/data/Shoot_bullet.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}
	result = m_Shoot_bullet_leftmap_no2->Initialize(m_D3D->GetDevice(), "../Engine/data/cube.txt", L"../Engine/data/Shoot_bullet.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}
	result = m_Shoot_bullet_leftmap_no3->Initialize(m_D3D->GetDevice(), "../Engine/data/cube.txt", L"../Engine/data/Shoot_bullet.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}
	result = m_Shoot_bullet_leftmap_no4->Initialize(m_D3D->GetDevice(), "../Engine/data/cube.txt", L"../Engine/data/Shoot_bullet.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}
	result = m_Shoot_bullet_leftmap_no5->Initialize(m_D3D->GetDevice(), "../Engine/data/cube.txt", L"../Engine/data/Shoot_bullet.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}
	result = m_Shoot_bullet_leftmap_no6->Initialize(m_D3D->GetDevice(), "../Engine/data/cube.txt", L"../Engine/data/Shoot_bullet.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}
	result = m_Shoot_bullet_leftmap_no7->Initialize(m_D3D->GetDevice(), "../Engine/data/cube.txt", L"../Engine/data/Shoot_bullet.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}
	result = m_Shoot_bullet_rightmap_no1->Initialize(m_D3D->GetDevice(), "../Engine/data/cube.txt", L"../Engine/data/Shoot_bullet.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}
	result = m_Shoot_bullet_rightmap_no2->Initialize(m_D3D->GetDevice(), "../Engine/data/cube.txt", L"../Engine/data/Shoot_bullet.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}
	result = m_Shoot_bullet_rightmap_no3->Initialize(m_D3D->GetDevice(), "../Engine/data/cube.txt", L"../Engine/data/Shoot_bullet.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}
	result = m_Shoot_bullet_rightmap_no4->Initialize(m_D3D->GetDevice(), "../Engine/data/cube.txt", L"../Engine/data/Shoot_bullet.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}
	result = m_Shoot_bullet_rightmap_no5->Initialize(m_D3D->GetDevice(), "../Engine/data/cube.txt", L"../Engine/data/Shoot_bullet.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}
	result = m_Map_1stMove->Initialize(m_D3D->GetDevice(), "../Engine/data/cube.txt", L"../Engine/data/Map.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}
	result = m_Map_2ndMove->Initialize(m_D3D->GetDevice(), "../Engine/data/cube.txt", L"../Engine/data/Map.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}
	result = m_Map_LeftFinish->Initialize(m_D3D->GetDevice(), "../Engine/data/cube.txt", L"../Engine/data/Map.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}
	result = m_Map_RightFinish->Initialize(m_D3D->GetDevice(), "../Engine/data/cube.txt", L"../Engine/data/Map.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}
	/////////////////////////////////////////////////////////////0621 추가   끝  by 지명근//////

	result = m_Human_Head->Initialize(m_D3D->GetDevice(), "../Engine/data/cube.txt", L"../Engine/data/HumanHead.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}
	result = m_Map->Initialize(m_D3D->GetDevice(), "../Engine/data/cube.txt", L"../Engine/data/Map.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}
	result = m_Human_Right_Arm->Initialize(m_D3D->GetDevice(), "../Engine/data/cube.txt", L"../Engine/data/HumanArm.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}
	result = m_Human_Right_Leg->Initialize(m_D3D->GetDevice(), "../Engine/data/cube.txt", L"../Engine/data/HumanLeg.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}
	result = m_Human_Body->Initialize(m_D3D->GetDevice(), "../Engine/data/cube.txt", L"../Engine/data/HumanBody.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}
	result = m_Human_Left_Arm->Initialize(m_D3D->GetDevice(), "../Engine/data/cube.txt", L"../Engine/data/HumanArm.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}
	result = m_UpDownObstaclee->Initialize(m_D3D->GetDevice(), "../Engine/data/cube.txt", L"../Engine/data/UpDownObs.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}
	result = m_Human_Left_Leg->Initialize(m_D3D->GetDevice(), "../Engine/data/cube.txt", L"../Engine/data/HumanLeg.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	//////////////////////0617 박민  Initialize the model object. 추가 시작/////////////////////////////////////////////

	for (int i = 0; i < 9; i++)
	{
		result = m_UpDownObstacle[i]->Initialize(m_D3D->GetDevice(), "../Engine/data/cube.txt", L"../Engine/data/UpDownObs.dds");
		if (!result)
		{
			MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
			return false;
		}
	}


	for (int i = 0; i < 24; i++)
	{
		result = m_RotObstacle[i]->Initialize(m_D3D->GetDevice(), "../Engine/data/cube.txt", L"../Engine/data/UpDownObs.dds");
		if (!result)
		{
			MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
			return false;
		}
	}
	result = m_Map2->Initialize(m_D3D->GetDevice(), "../Engine/data/cube.txt", L"../Engine/data/Map.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}
	result = m_Map3->Initialize(m_D3D->GetDevice(), "../Engine/data/cube.txt", L"../Engine/data/Map.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}
	for (int i = 0; i < 4; i++)
	{
		result = m_DynamicBoard[i]->Initialize(m_D3D->GetDevice(), "../Engine/data/cube.txt", L"../Engine/data/Map.dds");
		if (!result)
		{
			MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
			return false;
		}

	}

	for (int i = 0; i < 3; i++)
	{
		result = m_Stage2Map[i]->Initialize(m_D3D->GetDevice(), "../Engine/data/cube.txt", L"../Engine/data/map2.dds");
		if (!result)
		{
			MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
			return false;
		}

	}

	for (int i = 0; i < 4; i++)
	{
		result = m_Stage2background[i]->Initialize(m_D3D->GetDevice(), "../Engine/data/cube.txt", L"../Engine/data/stage3back.dds");
		if (!result)
		{
			MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
			return false;
		}

	}
	result = m_BBD->Initialize(m_D3D->GetDevice(), "../Engine/data/cube.txt", L"../Engine/data/Map.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}
	for (int i = 0; i < 3; i++)
	{
		result = m_AvoidObstacle[i]->Initialize(m_D3D->GetDevice(), "../Engine/data/cube.txt", L"../Engine/data/map2.dds");
		if (!result)
		{
			MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
			return false;
		}
	}
	for (int i = 3; i < 7; i++)
	{
		result = m_AvoidObstacle[i]->Initialize(m_D3D->GetDevice(), "../Engine/data/cube.txt", L"../Engine/data/Shoot_bullet.dds");
		if (!result)
		{
			MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
			return false;
		}
	}
	for (int i = 0; i < 7; i++)
	{
		result = m_BridgeObstacle[i]->Initialize(m_D3D->GetDevice(), "../Engine/data/cube.txt", L"../Engine/data/map2.dds");
		if (!result)
		{
			MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
			return false;
		}
	}
	for (int i = 7; i < 10; i++)
	{
		result = m_BridgeObstacle[i]->Initialize(m_D3D->GetDevice(), "../Engine/data/cube.txt", L"../Engine/data/Shoot_bullet.dds");
		if (!result)
		{
			MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
			return false;
		}
	}
	result = m_menu->Initialize(m_D3D->GetDevice(), "../Engine/data/cube.txt", L"../Engine/data/menu.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}
	for (int i = 0; i < 4; i++)
	{
		result = m_select[i]->Initialize(m_D3D->GetDevice(), "../Engine/data/cube.txt", L"../Engine/data/select.dds");
		if (!result)
		{
			MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
			return false;
		}
	}

	result = m_Stage1background->Initialize(m_D3D->GetDevice(), "../Engine/data/cube.txt", L"../Engine/data/Stage2back.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}


	//////////////////////0617 박민  Initialize the model object. 추가 끝/////////////////////////////////////////////

	// Create the light shader object.
	m_LightShader = new LightShaderClass;
	if (!m_LightShader)
	{
		return false;
	}

	// Initialize the light shader object.
	result = m_LightShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the light shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the light object.
	m_Light = new LightClass;
	if (!m_Light)
	{
		return false;
	}

	// Initialize the light object.
	m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetDirection(-1.0f, -1.0f, 0.4f); // 조명 수정 0621 박민 원래(0.0 , -1.0 , 1.0)

	return true;
}


void GraphicsClass::Shutdown()
{
	////////////////////////////////////////2016.06.20 김형륙 추가 시작
	if (m_RunControl)
	{
		delete m_RunControl;
		m_RunControl = 0;
	}
	if (m_Time)
	{
		delete m_Time;
		m_Time = 0;
	}
	if (m_RunGaze)
	{
		delete m_RunGaze;
		m_RunGaze = 0;
	}	
	if (m_HitCombo)
	{
		delete m_HitCombo;
		m_HitCombo = 0;
	}
	////////////////////////////////////////2016.06.20 김형륙 추가 끝
	// Release the light object.
	if (m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}

	// Release the light shader object.
	if (m_LightShader)
	{
		m_LightShader->Shutdown();
		delete m_LightShader;
		m_LightShader = 0;
	}

	// Release the model object.
	///////////////////////////////////////////////모델오브젝트 셧다운 추가 시작  by 지명근//////
	if (m_Shoot_bullet)
	{
		m_Shoot_bullet->Shutdown();
		delete m_Shoot_bullet;
		m_Shoot_bullet = 0;
	}
	if (m_Shoot_bullet_1stMove)
	{
		m_Shoot_bullet_1stMove->Shutdown();
		delete m_Shoot_bullet_1stMove;
		m_Shoot_bullet_1stMove = 0;
	}
	if (m_Shoot_bullet_2ndMove)
	{
		m_Shoot_bullet_2ndMove->Shutdown();
		delete m_Shoot_bullet_2ndMove;
		m_Shoot_bullet_2ndMove = 0;
	}
	if (m_Map_1stMove)
	{
		m_Map_1stMove->Shutdown();
		delete m_Map_1stMove;
		m_Map_1stMove = 0;
	}
	if (m_Map_2ndMove)
	{
		m_Map_2ndMove->Shutdown();
		delete m_Map_2ndMove;
		m_Map_2ndMove = 0;
	}
	///////////////////////////////////////////////모델오브젝트 셧다운 추가   끝  by 지명근//////
	///////////////////////////////////////////////0621 모델오브젝트 셧다운 추가 시작  by 지명근//////
	if (m_Shoot_bullet_3rdMove)
	{
		m_Shoot_bullet_3rdMove->Shutdown();
		delete m_Shoot_bullet_3rdMove;
		m_Shoot_bullet_3rdMove = 0;
	}
	if (m_Shoot_bullet_leftmap_no1)
	{
		m_Shoot_bullet_leftmap_no1->Shutdown();
		delete m_Shoot_bullet_leftmap_no1;
		m_Shoot_bullet_leftmap_no1 = 0;
	}
	if (m_Shoot_bullet_leftmap_no2)
	{
		m_Shoot_bullet_leftmap_no2->Shutdown();
		delete m_Shoot_bullet_leftmap_no2;
		m_Shoot_bullet_leftmap_no2 = 0;
	}
	if (m_Shoot_bullet_leftmap_no3)
	{
		m_Shoot_bullet_leftmap_no3->Shutdown();
		delete m_Shoot_bullet_leftmap_no3;
		m_Shoot_bullet_leftmap_no3 = 0;
	}
	if (m_Shoot_bullet_leftmap_no4)
	{
		m_Shoot_bullet_leftmap_no4->Shutdown();
		delete m_Shoot_bullet_leftmap_no4;
		m_Shoot_bullet_leftmap_no4 = 0;
	}
	if (m_Shoot_bullet_leftmap_no5)
	{
		m_Shoot_bullet_leftmap_no5->Shutdown();
		delete m_Shoot_bullet_leftmap_no5;
		m_Shoot_bullet_leftmap_no5 = 0;
	}
	if (m_Shoot_bullet_leftmap_no6)
	{
		m_Shoot_bullet_leftmap_no6->Shutdown();
		delete m_Shoot_bullet_leftmap_no6;
		m_Shoot_bullet_leftmap_no6 = 0;
	}
	if (m_Shoot_bullet_leftmap_no7)
	{
		m_Shoot_bullet_leftmap_no7->Shutdown();
		delete m_Shoot_bullet_leftmap_no7;
		m_Shoot_bullet_leftmap_no7 = 0;
	}
	if (m_Shoot_bullet_rightmap_no1)
	{
		m_Shoot_bullet_rightmap_no1->Shutdown();
		delete m_Shoot_bullet_rightmap_no1;
		m_Shoot_bullet_rightmap_no1 = 0;
	}
	if (m_Shoot_bullet_rightmap_no2)
	{
		m_Shoot_bullet_rightmap_no2->Shutdown();
		delete m_Shoot_bullet_rightmap_no2;
		m_Shoot_bullet_rightmap_no2 = 0;
	}
	if (m_Shoot_bullet_rightmap_no3)
	{
		m_Shoot_bullet_rightmap_no3->Shutdown();
		delete m_Shoot_bullet_rightmap_no3;
		m_Shoot_bullet_rightmap_no3 = 0;
	}
	if (m_Shoot_bullet_rightmap_no4)
	{
		m_Shoot_bullet_rightmap_no4->Shutdown();
		delete m_Shoot_bullet_rightmap_no4;
		m_Shoot_bullet_rightmap_no4 = 0;
	}
	if (m_Map_LeftFinish)
	{
		m_Map_LeftFinish->Shutdown();
		delete m_Map_LeftFinish;
		m_Map_LeftFinish = 0;
	}
	if (m_Map_RightFinish)
	{
		m_Map_LeftFinish->Shutdown();
		delete m_Map_LeftFinish;
		m_Map_LeftFinish = 0;
	}

	///////////////////////////////////////////////0621 모델오브젝트 셧다운 추가   끝  by 지명근//////
	if (m_Human_Right_Arm)
	{
		m_Human_Right_Arm->Shutdown();
		delete m_Human_Right_Arm;
		m_Human_Right_Arm = 0;
	}
	if (m_Map)
	{
		m_Map->Shutdown();
		delete m_Map;
		m_Map = 0;
	}
	if (m_Human_Right_Leg)
	{
		m_Human_Right_Leg->Shutdown();
		delete m_Human_Right_Leg;
		m_Human_Right_Leg = 0;
	}
	if (m_Human_Head)
	{
		m_Human_Head->Shutdown();
		delete m_Human_Head;
		m_Human_Head = 0;
	}
	if (m_Human_Body)
	{
		m_Human_Body->Shutdown();
		delete m_Human_Body;
		m_Human_Body = 0;
	}
	if (m_Human_Left_Leg)
	{
		m_Human_Left_Leg->Shutdown();
		delete m_Human_Left_Leg;
		m_Human_Left_Leg = 0;
	}
	if (m_UpDownObstaclee)
	{
		m_UpDownObstaclee->Shutdown();
		delete m_UpDownObstaclee;
		m_UpDownObstaclee = 0;
	}
	if (m_Human_Left_Arm)
	{
		m_Human_Left_Arm->Shutdown();
		delete m_Human_Left_Arm;
		m_Human_Left_Arm = 0;
	}
	/////////////////////////////0617 박민  Release the model object. 셧다운 추가 시작/////////////////////////////
	for (int i = 0; i < 9; i++)
	{
		if (m_UpDownObstacle[i])
		{
			m_UpDownObstacle[i]->Shutdown();
			delete m_UpDownObstacle[i];
			m_UpDownObstacle[i] = 0;
		}
	}

	for (int i = 0; i < 24; i++)
	{
		if (m_RotObstacle[i])
		{
			m_RotObstacle[i]->Shutdown();
			delete m_RotObstacle[i];
			m_RotObstacle[i] = 0;
		}
	}
	if (m_Map2)
	{
		m_Map2->Shutdown();
		delete m_Map2;
		m_Map2 = 0;
	}
	if (m_Map3)
	{
		m_Map3->Shutdown();
		delete m_Map3;
		m_Map3 = 0;
	}
	for (int i = 0; i < 4; i++)
	{
		if (m_DynamicBoard[i])
		{
			m_DynamicBoard[i]->Shutdown();
			delete m_DynamicBoard[i];
			m_DynamicBoard[i] = 0;
		}
	}
	for (int i = 0; i < 3; i++)
	{
		if (m_Stage2Map[i])
		{
			m_Stage2Map[i]->Shutdown();
			delete m_Stage2Map[i];
			m_Stage2Map[i] = 0;
		}
	}
	for (int i = 0; i < 4; i++)
	{
		if (m_Stage2background[i])
		{
			m_Stage2background[i]->Shutdown();
			delete m_Stage2background[i];
			m_Stage2background[i] = 0;
		}
	}


	if (m_BBD)
	{
		m_BBD->Shutdown();
		delete m_BBD;
		m_BBD = 0;
	}

	for (int i = 0; i < 7; i++)
	{
		if (m_AvoidObstacle[i])
		{
			m_AvoidObstacle[i]->Shutdown();
			delete m_AvoidObstacle[i];
			m_AvoidObstacle[i] = 0;
		}
	}

	for (int i = 0; i < 10; i++)
	{
		if (m_BridgeObstacle[i])
		{
			m_BridgeObstacle[i]->Shutdown();
			delete m_BridgeObstacle[i];
			m_BridgeObstacle[i] = 0;
		}
	}
	if (m_menu)
	{
		m_menu->Shutdown();
		delete m_menu;
		m_menu = 0;
	}
	for (int i = 0; i < 4; i++)
	{
		if (m_select[i])
		{
			m_select[i]->Shutdown();
			delete m_select[i];
			m_select[i] = 0;
		}
	}

	if (m_Stage1background)
	{
		m_Stage1background->Shutdown();
		delete m_Stage1background;
		m_Stage1background = 0;
	}



	/////////////////////////////0617 박민  Release the model object. 셧다운 추가 끝/////////////////////////////

	// Release the camera object.
	if (m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// Release the D3D object.
	if (m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

	return;
}

bool GraphicsClass::Frame()
{
	bool result;
	static float rotation = 0.0f;

	// Update the rotation variable each frame.
	rotation += (float)D3DX_PI * 0.05f;
	if (rotation > 10.0f)
	{
		rotation -= 10.0f;
	}

	// Render the graphics scene.
	result = Render(rotation);
	if (!result)
	{
		return false;
	}

	return true;
}
/////////////////////////////////////////////김형륙 2016/06/18 추가
float timeTemp = 0.0f;
bool checkLeft = false;
float i, j, k,a,b,c;
bool checkStartTime = true;
float runControlX; 
float tempFloat;
bool tempFloatIncrease = true;
bool tempFloatDecrease = false;
bool isRunHit = false;
float hitX, hitY, hitZ;
bool isSitDown = false;
float speed = 0.1f;
bool speedReset = false;
/////////////////////////////////////////////김형륙 2016/06/18 추가끝
bool GraphicsClass::Render(float second)
{
	D3DXMATRIX temp;
	D3DXMATRIX move;
	if (stage == 0)
	{
		D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix;
		bool result;

		// Clear the buffers to begin the scene.
		m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

		// Generate the view matrix based on the camera's position.
		m_Camera->Render();

		// Get the world, view, and projection matrices from the camera and d3d objects.
		m_Camera->GetViewMatrix(viewMatrix);
		m_D3D->GetWorldMatrix(worldMatrix);
		m_D3D->GetProjectionMatrix(projectionMatrix);
		
		D3DXMATRIX menu;
		D3DXMATRIX temp;
		D3DXMATRIX select[4];

		D3DXMatrixRotationY(&temp , 1.6f);
		D3DXMatrixTranslation(&viewMatrix, -50.0f, 0.0f, -1.7f);
		viewMatrix *= temp;
		D3DXMatrixScaling(&menu, 0.3f, 23.0f, 38.0f);
		D3DXMatrixTranslation(&temp, 0.0f, 5.0f, 0.0f);
		menu *= temp;
		/*
		m_Camera->SetPosition(50.0f, 0.0f, 0.0f);
		m_Camera->SetLookat(-1.0f, 0.0f, 0.0f);*/
		//m_Camera->SetPosition(0.0f, 0.0f, 0.0f);
		D3DXMatrixTranslation(&temp, 0.0f, -3.0f, 0.0f);
		worldMatrix *= temp;
		m_menu->Render(m_D3D->GetDeviceContext());
		// Render the model using the light shader.
		result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_menu->GetIndexCount(), menu * worldMatrix, viewMatrix, projectionMatrix,
			m_menu->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
		if (!result)
		{
			return false;
		}

		for (int i = 0; i < 4; i++)
		{
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_select[i]->GetIndexCount(), select[i] * worldMatrix, viewMatrix, projectionMatrix,
				m_select[i]->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
		}

		if (m_input->IsKeyDown(87) || m_input->IsKeyDown(119)) {

			selecty = 10.0f;
			selectz = 26.5f;


		}
		if (m_input->IsKeyDown(83) || m_input->IsKeyDown(115)) {

			selecty = -7.0f;
			selectz = 26.5f;
		}

		if (m_input->IsKeyDown(32))
		{
			if (selecty == 10.0f)
				stage = 1;

			else if (selecty == -7.0f)
			{
				PostQuitMessage(0);
				return 0;
			}

		}
		D3DXMatrixScaling(&select[0], 0.3f, 0.5f, 7.0f);
		D3DXMatrixTranslation(&temp, 2.0f, selecty + 5.0f, selectz + 0.0f);
		select[0] *= temp;
		D3DXMatrixScaling(&select[1], 0.3f, 5.0f, 0.5f);
		D3DXMatrixTranslation(&temp, 2.0f, selecty + 0.0f, selectz + -6.5f);
		select[1] *= temp;
		D3DXMatrixScaling(&select[2], 0.3f, 0.5f, 7.0f);
		D3DXMatrixTranslation(&temp, 2.0f, selecty - 5.0f, selectz + 0.0f);
		select[2] *= temp;
		D3DXMatrixScaling(&select[3], 0.3f, 5.0f, 0.5f);
		D3DXMatrixTranslation(&temp, 2.0f, selecty + 0.0f, selectz + 6.5f);
		select[3] *= temp;




		m_D3D->EndScene();
		return true;
	}
	else if(stage>=1) {

		D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix;
		bool result;

		// Clear the buffers to begin the scene.
		m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

		// Generate the view matrix based on the camera's position.
		m_Camera->Render();

		// Get the world, view, and projection matrices from the camera and d3d objects.
		m_Camera->GetViewMatrix(viewMatrix);
		m_D3D->GetWorldMatrix(worldMatrix);
		m_D3D->GetProjectionMatrix(projectionMatrix);

	
		// Rotate the world matrix by the rotation value so that the triangle will spin.
		D3DXMATRIX HumanHead;
		D3DXMATRIX HumanBody;
		D3DXMATRIX Time;
		D3DXMATRIX HumanLeftLeg;
		D3DXMATRIX HumanLeftArm;
		D3DXMATRIX HumanRightLeg;
		D3DXMATRIX HumanRightArm;
		
		D3DXMATRIX Map;
		D3DXMATRIX rotate;
		D3DXMATRIX timeSet;
		D3DXMATRIX runGaze;
		D3DXMATRIX runGazeControl;
		D3DXMATRIX hitCombo;

		bool checkMoveLeg = false;
		///////////////////////////////////////////////////////////////static 시간 t 추가//////
		static float t = 0.0f;
		///////////////////////////////////////////////////////////////2016/06/16 김형륙 추가
		static float jumpT = 0.0f;
		///////////////////////////////////////////////////////////////2016/06/16 김형륙 추가끝
		static ULONGLONG timeStart = 0;
		ULONGLONG timeCur = GetTickCount64();
		if (timeStart == 0)
			timeStart = timeCur;
		t = (timeCur - timeStart) / 500.0f;
		///////////////////////////////////////////////////////////////2016/06/16 김형륙 추가
		jumpT = (timeCur - timeStart) / 100.0f;
		///////////////////////////////////////////////////////////////2016/06/16 김형륙 추가끝
		///////////////////////////////////////////////////////////////static 시간 t 종료///
		
		D3DXMatrixScaling(&HumanHead, 0.3f, 0.3f, 0.3f);
		D3DXMatrixScaling(&HumanBody, 0.5f, 1.0f, 0.3f);
		D3DXMatrixScaling(&HumanLeftLeg, 0.2f, 1.0f, 0.3f);
		D3DXMatrixScaling(&HumanLeftArm, 0.15f, 0.8f, 0.2f);
		D3DXMatrixScaling(&HumanRightLeg, 0.2f, 1.0f, 0.3f);
		D3DXMatrixScaling(&HumanRightArm, 0.15f, 0.8f, 0.2f);


		if (m_input->IsKeyDown(87) || m_input->IsKeyDown(119)) {
			x = x - speed;
			checkMoveLeg = true;
		}
		if (m_input->IsKeyDown(83) || m_input->IsKeyDown(115)) {
			x = x + speed;
			checkMoveLeg = true;
		}

		if (m_input->IsKeyDown(68) || m_input->IsKeyDown(100)) {
			left = left + 0.1f;
			checkLeft = true;
			checkMoveLeg = true;
		}
		if (m_input->IsKeyDown(65) || m_input->IsKeyDown(97)) {
			left = left - 0.1f;
			checkLeft = true;
			checkMoveLeg = true;
		}

		if (m_input->IsKeyDown(67) || m_input->IsKeyDown(99)) {
			isSitDown = true;
			speed = 0.05f;
			speedReset = true;
		}
		if (m_input->IsKeyDown(81) || m_input->IsKeyDown(113)) {
			isLook1st = !isLook1st;
		}
		if (m_input->IsKeyDown(32)) {
			if (tempFloat >= 1.5f || tempFloat <= -1.5f) {
				speed += 0.03f;
			}
			else {
				speed = 0.1f;
			}
		}
		if (speedReset&&!(m_input->IsKeyDown(67) || m_input->IsKeyDown(99))) {
			speed = 0.1f;
			speedReset = false;
		}
		if ((m_input->IsKeyDown(70) || m_input->IsKeyDown(102)) && jumpposition == 0.0f) {
			jumppress = 1.0f;
			checkJump = true;
		}
		if (checkMoveLeg) {
			D3DXMatrixTranslation(&temp, 0.0f, -0.7f, 0.0f);
			HumanLeftLeg *= temp;
			HumanRightLeg *= temp;
			D3DXMatrixRotationX(&temp, (float)((int)second % 2));
			HumanLeftLeg *= temp;
			D3DXMatrixRotationX(&temp, (-1)*(float)((int)second % 2));
			HumanRightLeg *= temp;
			D3DXMatrixTranslation(&temp, 0.0f, 0.7f, 0.0f);
			HumanLeftLeg *= temp;
			HumanRightLeg *= temp;
			D3DXMatrixTranslation(&temp, 0.0f, 0.2f, 0.0f);
			HumanLeftLeg *= temp;
			HumanRightLeg *= temp;
			D3DXMatrixTranslation(&temp, 0.0f, -0.7f, 0.0f);
			HumanLeftArm *= temp;
			HumanRightArm *= temp;
			D3DXMatrixRotationX(&temp, (float)((int)second % 2));
			HumanLeftArm *= temp;
			D3DXMatrixRotationX(&temp, (-1)*(float)((int)second % 2));
			HumanRightArm *= temp;
			D3DXMatrixTranslation(&temp, 0.0f, 0.7f, 0.0f);
			HumanLeftArm *= temp;
			HumanRightArm *= temp;
			D3DXMatrixTranslation(&temp, 0.0f, -0.15f, 0.0f);
			HumanLeftArm *= temp;
			HumanRightArm *= temp;
		}
		if (isSitDown) {
			D3DXMatrixTranslation(&temp, 0.0f, 0.0f, 0.0f);
			HumanHead *= temp;
		}
		else {
			D3DXMatrixTranslation(&temp, 0.0f, 2.0f, 0.0f);
			HumanHead *= temp;
		}
		if (isSitDown) {
			D3DXMatrixTranslation(&temp, 0.0f, -1.2f, 0.0f);
			HumanBody *= temp;
		}
		else {
			D3DXMatrixTranslation(&temp, 0.0f, 0.7f, 0.0f);
			HumanBody *= temp;
		}
		D3DXMatrixTranslation(&temp, -0.25f, -1.3f, 0.0f);
		HumanLeftLeg *= temp;
		D3DXMatrixTranslation(&temp, 0.25f, -1.3f, 0.0f);
		HumanRightLeg *= temp;
		if (isSitDown) {
			D3DXMatrixTranslation(&temp, -0.7f, -1.4f, 0.0f);
			HumanLeftArm *= temp;
			D3DXMatrixTranslation(&temp, 0.7f, -1.4f, 0.0f);
			HumanRightArm *= temp;
			isSitDown = false;
		}
		else {
			D3DXMatrixTranslation(&temp, -0.7f, 0.9f, 0.0f);
			HumanLeftArm *= temp;
			D3DXMatrixTranslation(&temp, 0.7f, 0.9f, 0.0f);
			HumanRightArm *= temp;
		}
		if (checkLeft) {
			D3DXMatrixTranslation(&temp, i, j, k);
			D3DXMatrixRotationY(&rotate, left);
			sumAllMovement = (temp*rotate);
			checkLeft = false;
			sumAllMovement._41 = i;
			sumAllMovement._42 = j;
			sumAllMovement._43 = k;
			x = 0.0f;
			a = i;
			b = j;
			c = k;
		}
		else {
			sumAllMovement._43 = x*cos(left) + c;
			sumAllMovement._41 = x*sin(left) + a;
			i = sumAllMovement._41;
			j = sumAllMovement._42;
			k = sumAllMovement._43;
		}

		D3DXMatrixTranslation(&viewMatrix, 0.0f, 0.0f, -k + 23.0f);
		m_Time->Render(m_D3D->GetDeviceContext());
		clock_t begin, end;
		if (checkStartTime) {
			begin = clock();
			checkStartTime = false;
		}
		end = clock();
		D3DXMatrixTranslation(&timeSet, 0.6f, 0.0f, 0.0f);
		switch ((end / 1000) % 10) {
		case 0:
			D3DXMatrixScaling(&Time, 0.1f, 0.02f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.0f, 3.0f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			D3DXMatrixScaling(&Time, 0.02f, 0.1f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.147f, 2.87f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}

			D3DXMatrixScaling(&Time, 0.02f, 0.1f, 0.01f);
			D3DXMatrixTranslation(&temp, -0.147f, 2.87f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			D3DXMatrixScaling(&Time, 0.02f, 0.1f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.147f, 2.6f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}

			D3DXMatrixScaling(&Time, 0.02f, 0.1f, 0.01f);
			D3DXMatrixTranslation(&temp, -0.147f, 2.6f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			D3DXMatrixScaling(&Time, 0.1f, 0.02f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.0f, 2.48f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			break;
		case 1:
			D3DXMatrixScaling(&Time, 0.02f, 0.1f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.147f, 2.87f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			D3DXMatrixScaling(&Time, 0.02f, 0.1f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.147f, 2.6f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}

			break;
		case 2:
			D3DXMatrixScaling(&Time, 0.1f, 0.02f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.0f, 3.0f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			D3DXMatrixScaling(&Time, 0.02f, 0.1f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.147f, 2.87f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			D3DXMatrixScaling(&Time, 0.1f, 0.02f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.0f, 2.75f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}	D3DXMatrixScaling(&Time, 0.02f, 0.1f, 0.01f);
			D3DXMatrixTranslation(&temp, -0.147f, 2.6f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			D3DXMatrixScaling(&Time, 0.1f, 0.02f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.0f, 2.48f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			break;
		case 3:
			D3DXMatrixScaling(&Time, 0.1f, 0.02f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.0f, 3.0f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			D3DXMatrixScaling(&Time, 0.02f, 0.1f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.147f, 2.87f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}	D3DXMatrixScaling(&Time, 0.1f, 0.02f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.0f, 2.75f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			D3DXMatrixScaling(&Time, 0.02f, 0.1f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.147f, 2.6f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			D3DXMatrixScaling(&Time, 0.1f, 0.02f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.0f, 2.48f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			break;
		case 4:
			D3DXMatrixScaling(&Time, 0.02f, 0.1f, 0.01f);
			D3DXMatrixTranslation(&temp, -0.147f, 2.87f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}	D3DXMatrixScaling(&Time, 0.1f, 0.02f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.0f, 2.75f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}	D3DXMatrixScaling(&Time, 0.02f, 0.1f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.147f, 2.87f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			D3DXMatrixScaling(&Time, 0.02f, 0.1f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.147f, 2.6f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			break;
		case 5:
			D3DXMatrixScaling(&Time, 0.1f, 0.02f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.0f, 3.0f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}	D3DXMatrixScaling(&Time, 0.02f, 0.1f, 0.01f);
			D3DXMatrixTranslation(&temp, -0.147f, 2.87f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}	D3DXMatrixScaling(&Time, 0.1f, 0.02f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.0f, 2.75f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}	D3DXMatrixScaling(&Time, 0.02f, 0.1f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.147f, 2.6f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			D3DXMatrixScaling(&Time, 0.1f, 0.02f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.0f, 2.48f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			break;
		case 6:
			D3DXMatrixScaling(&Time, 0.1f, 0.02f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.0f, 3.0f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}	D3DXMatrixScaling(&Time, 0.02f, 0.1f, 0.01f);
			D3DXMatrixTranslation(&temp, -0.147f, 2.87f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			D3DXMatrixScaling(&Time, 0.1f, 0.02f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.0f, 2.75f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			D3DXMatrixScaling(&Time, 0.02f, 0.1f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.147f, 2.6f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}

			D3DXMatrixScaling(&Time, 0.02f, 0.1f, 0.01f);
			D3DXMatrixTranslation(&temp, -0.147f, 2.6f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			D3DXMatrixScaling(&Time, 0.1f, 0.02f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.0f, 2.48f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			break;
		case 7:
			D3DXMatrixScaling(&Time, 0.1f, 0.02f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.0f, 3.0f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			D3DXMatrixScaling(&Time, 0.02f, 0.1f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.147f, 2.87f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			D3DXMatrixScaling(&Time, 0.02f, 0.1f, 0.01f);
			D3DXMatrixTranslation(&temp, -0.147f, 2.87f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}	D3DXMatrixScaling(&Time, 0.02f, 0.1f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.147f, 2.6f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			break;
		case 8:
			D3DXMatrixScaling(&Time, 0.1f, 0.02f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.0f, 3.0f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			D3DXMatrixScaling(&Time, 0.02f, 0.1f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.147f, 2.87f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}

			D3DXMatrixScaling(&Time, 0.02f, 0.1f, 0.01f);
			D3DXMatrixTranslation(&temp, -0.147f, 2.87f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			D3DXMatrixScaling(&Time, 0.1f, 0.02f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.0f, 2.75f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			D3DXMatrixScaling(&Time, 0.02f, 0.1f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.147f, 2.6f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}

			D3DXMatrixScaling(&Time, 0.02f, 0.1f, 0.01f);
			D3DXMatrixTranslation(&temp, -0.147f, 2.6f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			D3DXMatrixScaling(&Time, 0.1f, 0.02f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.0f, 2.48f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			break;
		case 9:
			D3DXMatrixScaling(&Time, 0.1f, 0.02f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.0f, 3.0f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			D3DXMatrixScaling(&Time, 0.02f, 0.1f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.147f, 2.87f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}

			D3DXMatrixScaling(&Time, 0.02f, 0.1f, 0.01f);
			D3DXMatrixTranslation(&temp, -0.147f, 2.87f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			D3DXMatrixScaling(&Time, 0.1f, 0.02f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.0f, 2.75f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			D3DXMatrixScaling(&Time, 0.02f, 0.1f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.147f, 2.6f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}	D3DXMatrixScaling(&Time, 0.1f, 0.02f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.0f, 2.48f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			break;
		}
		/////////////////////////////////////////////초 십의자리
		D3DXMatrixTranslation(&timeSet, 0.15f, 0.0f, 0.0f);
		switch (((end / 1000) / 10) % 6) {
		case 0:
			D3DXMatrixScaling(&Time, 0.1f, 0.02f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.0f, 3.0f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			D3DXMatrixScaling(&Time, 0.02f, 0.1f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.147f, 2.87f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}

			D3DXMatrixScaling(&Time, 0.02f, 0.1f, 0.01f);
			D3DXMatrixTranslation(&temp, -0.147f, 2.87f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			D3DXMatrixScaling(&Time, 0.02f, 0.1f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.147f, 2.6f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}

			D3DXMatrixScaling(&Time, 0.02f, 0.1f, 0.01f);
			D3DXMatrixTranslation(&temp, -0.147f, 2.6f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			D3DXMatrixScaling(&Time, 0.1f, 0.02f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.0f, 2.48f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			break;
		case 1:
			D3DXMatrixScaling(&Time, 0.02f, 0.1f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.147f, 2.87f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			D3DXMatrixScaling(&Time, 0.02f, 0.1f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.147f, 2.6f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}

			break;
		case 2:
			D3DXMatrixScaling(&Time, 0.1f, 0.02f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.0f, 3.0f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			D3DXMatrixScaling(&Time, 0.02f, 0.1f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.147f, 2.87f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			D3DXMatrixScaling(&Time, 0.1f, 0.02f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.0f, 2.75f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}	D3DXMatrixScaling(&Time, 0.02f, 0.1f, 0.01f);
			D3DXMatrixTranslation(&temp, -0.147f, 2.6f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			D3DXMatrixScaling(&Time, 0.1f, 0.02f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.0f, 2.48f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			break;
		case 3:
			D3DXMatrixScaling(&Time, 0.1f, 0.02f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.0f, 3.0f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			D3DXMatrixScaling(&Time, 0.02f, 0.1f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.147f, 2.87f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}	D3DXMatrixScaling(&Time, 0.1f, 0.02f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.0f, 2.75f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			D3DXMatrixScaling(&Time, 0.02f, 0.1f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.147f, 2.6f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			D3DXMatrixScaling(&Time, 0.1f, 0.02f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.0f, 2.48f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			break;
		case 4:
			D3DXMatrixScaling(&Time, 0.02f, 0.1f, 0.01f);
			D3DXMatrixTranslation(&temp, -0.147f, 2.87f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}	D3DXMatrixScaling(&Time, 0.1f, 0.02f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.0f, 2.75f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}	D3DXMatrixScaling(&Time, 0.02f, 0.1f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.147f, 2.87f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			D3DXMatrixScaling(&Time, 0.02f, 0.1f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.147f, 2.6f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			break;
		case 5:
			D3DXMatrixScaling(&Time, 0.1f, 0.02f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.0f, 3.0f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}	D3DXMatrixScaling(&Time, 0.02f, 0.1f, 0.01f);
			D3DXMatrixTranslation(&temp, -0.147f, 2.87f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}	D3DXMatrixScaling(&Time, 0.1f, 0.02f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.0f, 2.75f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}	D3DXMatrixScaling(&Time, 0.02f, 0.1f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.147f, 2.6f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			D3DXMatrixScaling(&Time, 0.1f, 0.02f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.0f, 2.48f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			break;
		}
		D3DXMatrixScaling(&Time, 0.05f, 0.05f, 0.01f);
		D3DXMatrixTranslation(&temp, -0.15f, 2.9f, k - 15.0f);
		Time *= temp;
		result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time, viewMatrix, projectionMatrix,
			m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
		if (!result)
		{
			return false;
		}
		D3DXMatrixScaling(&Time, 0.05f, 0.05f, 0.01f);
		D3DXMatrixTranslation(&temp, -0.15f, 2.6f, k - 15.0f);
		Time *= temp;
		result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time, viewMatrix, projectionMatrix,
			m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
		if (!result)
		{
			return false;
		}

		/////////////////////////////////////////////분 일의자리
		D3DXMatrixTranslation(&timeSet, -0.4f, 0.0f, 0.0f);
		switch ((end / 1000) / 60) {
		case 0:
			D3DXMatrixScaling(&Time, 0.1f, 0.02f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.0f, 3.0f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			D3DXMatrixScaling(&Time, 0.02f, 0.1f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.147f, 2.87f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}

			D3DXMatrixScaling(&Time, 0.02f, 0.1f, 0.01f);
			D3DXMatrixTranslation(&temp, -0.147f, 2.87f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			D3DXMatrixScaling(&Time, 0.02f, 0.1f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.147f, 2.6f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}

			D3DXMatrixScaling(&Time, 0.02f, 0.1f, 0.01f);
			D3DXMatrixTranslation(&temp, -0.147f, 2.6f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			D3DXMatrixScaling(&Time, 0.1f, 0.02f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.0f, 2.48f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			break;
		case 1:
			D3DXMatrixScaling(&Time, 0.02f, 0.1f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.147f, 2.87f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			D3DXMatrixScaling(&Time, 0.02f, 0.1f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.147f, 2.6f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}

			break;
		case 2:
			D3DXMatrixScaling(&Time, 0.1f, 0.02f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.0f, 3.0f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			D3DXMatrixScaling(&Time, 0.02f, 0.1f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.147f, 2.87f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			D3DXMatrixScaling(&Time, 0.1f, 0.02f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.0f, 2.75f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}	D3DXMatrixScaling(&Time, 0.02f, 0.1f, 0.01f);
			D3DXMatrixTranslation(&temp, -0.147f, 2.6f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			D3DXMatrixScaling(&Time, 0.1f, 0.02f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.0f, 2.48f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			break;
		case 3:
			D3DXMatrixScaling(&Time, 0.1f, 0.02f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.0f, 3.0f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			D3DXMatrixScaling(&Time, 0.02f, 0.1f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.147f, 2.87f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}	D3DXMatrixScaling(&Time, 0.1f, 0.02f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.0f, 2.75f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			D3DXMatrixScaling(&Time, 0.02f, 0.1f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.147f, 2.6f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			D3DXMatrixScaling(&Time, 0.1f, 0.02f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.0f, 2.48f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			break;
		case 4:
			D3DXMatrixScaling(&Time, 0.02f, 0.1f, 0.01f);
			D3DXMatrixTranslation(&temp, -0.147f, 2.87f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}	D3DXMatrixScaling(&Time, 0.1f, 0.02f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.0f, 2.75f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}	D3DXMatrixScaling(&Time, 0.02f, 0.1f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.147f, 2.87f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			D3DXMatrixScaling(&Time, 0.02f, 0.1f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.147f, 2.6f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			break;
		case 5:
			D3DXMatrixScaling(&Time, 0.1f, 0.02f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.0f, 3.0f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}	D3DXMatrixScaling(&Time, 0.02f, 0.1f, 0.01f);
			D3DXMatrixTranslation(&temp, -0.147f, 2.87f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}	D3DXMatrixScaling(&Time, 0.1f, 0.02f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.0f, 2.75f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}	D3DXMatrixScaling(&Time, 0.02f, 0.1f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.147f, 2.6f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			D3DXMatrixScaling(&Time, 0.1f, 0.02f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.0f, 2.48f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			break;
		case 6:
			D3DXMatrixScaling(&Time, 0.1f, 0.02f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.0f, 3.0f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}	D3DXMatrixScaling(&Time, 0.02f, 0.1f, 0.01f);
			D3DXMatrixTranslation(&temp, -0.147f, 2.87f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			D3DXMatrixScaling(&Time, 0.1f, 0.02f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.0f, 2.75f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			D3DXMatrixScaling(&Time, 0.02f, 0.1f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.147f, 2.6f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}

			D3DXMatrixScaling(&Time, 0.02f, 0.1f, 0.01f);
			D3DXMatrixTranslation(&temp, -0.147f, 2.6f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			D3DXMatrixScaling(&Time, 0.1f, 0.02f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.0f, 2.48f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			break;
		case 7:
			D3DXMatrixScaling(&Time, 0.1f, 0.02f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.0f, 3.0f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			D3DXMatrixScaling(&Time, 0.02f, 0.1f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.147f, 2.87f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			D3DXMatrixScaling(&Time, 0.02f, 0.1f, 0.01f);
			D3DXMatrixTranslation(&temp, -0.147f, 2.87f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}	D3DXMatrixScaling(&Time, 0.02f, 0.1f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.147f, 2.6f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			break;
		case 8:
			D3DXMatrixScaling(&Time, 0.1f, 0.02f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.0f, 3.0f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			D3DXMatrixScaling(&Time, 0.02f, 0.1f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.147f, 2.87f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}

			D3DXMatrixScaling(&Time, 0.02f, 0.1f, 0.01f);
			D3DXMatrixTranslation(&temp, -0.147f, 2.87f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			D3DXMatrixScaling(&Time, 0.1f, 0.02f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.0f, 2.75f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			D3DXMatrixScaling(&Time, 0.02f, 0.1f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.147f, 2.6f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}

			D3DXMatrixScaling(&Time, 0.02f, 0.1f, 0.01f);
			D3DXMatrixTranslation(&temp, -0.147f, 2.6f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			D3DXMatrixScaling(&Time, 0.1f, 0.02f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.0f, 2.48f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			break;
		case 9:
			D3DXMatrixScaling(&Time, 0.1f, 0.02f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.0f, 3.0f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			D3DXMatrixScaling(&Time, 0.02f, 0.1f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.147f, 2.87f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}

			D3DXMatrixScaling(&Time, 0.02f, 0.1f, 0.01f);
			D3DXMatrixTranslation(&temp, -0.147f, 2.87f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			D3DXMatrixScaling(&Time, 0.1f, 0.02f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.0f, 2.75f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			D3DXMatrixScaling(&Time, 0.02f, 0.1f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.147f, 2.6f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}	D3DXMatrixScaling(&Time, 0.1f, 0.02f, 0.01f);
			D3DXMatrixTranslation(&temp, 0.0f, 2.48f, k - 15.0f);
			Time *= temp;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Time->GetIndexCount(), Time*timeSet, viewMatrix, projectionMatrix,
				m_Time->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			break;
		}
		D3DXMatrixScaling(&runGaze, 2.1f, 0.1f, 0.01f);
		D3DXMatrixTranslation(&temp, 0.0f, -3.0f, k - 15.0f);
		runGaze *= temp;
		result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_RunGaze->GetIndexCount(), runGaze, viewMatrix, projectionMatrix,
			m_RunGaze->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
		if (!result)
		{
			return false;
		}
		////////////////////////////////////////////////////바에서 사각형이동
		D3DXMatrixScaling(&runGazeControl, 0.1f, 0.1f, 0.01f);
		if (tempFloatIncrease) {
			tempFloat += 0.12f;
			if (tempFloat >= 2.0f) {
				tempFloatIncrease = false;
				tempFloatDecrease = true;
			}
		}
		if (tempFloatDecrease) {
			tempFloat -= 0.12f;
			if (tempFloat <= -2.0f) {
				tempFloatIncrease = true;
				tempFloatDecrease = false;
			}
		}
		if (!isLook1st) {
			D3DXMatrixTranslation(&temp, -40.0f, 0.0f, -30.0f);
			viewMatrix *= temp;
			D3DXMatrixRotationY(&temp, 1.6f);
			viewMatrix *= temp;
		}
		D3DXMatrixTranslation(&temp, tempFloat, -2.954f, k - 15.1f);					//2.0에서 -2.0까지
		runGazeControl *= temp;
		result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_RunControl->GetIndexCount(), runGazeControl, viewMatrix, projectionMatrix,
			m_RunControl->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
		if (!result)
		{
			return false;
		}
		m_Human_Right_Leg->Render(m_D3D->GetDeviceContext());
		// Render the model using the light shader.
		result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Human_Right_Leg->GetIndexCount(), HumanRightLeg*worldMatrix*sumAllMovement, viewMatrix, projectionMatrix,
			m_Human_Right_Leg->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
		if (!result)
		{
			return false;
		}
		m_Human_Right_Arm->Render(m_D3D->GetDeviceContext());
		// Render the model using the light shader.
		result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Human_Right_Arm->GetIndexCount(), HumanRightArm* sumAllMovement*worldMatrix, viewMatrix, projectionMatrix,
			m_Human_Right_Arm->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
		if (!result)
		{
			return false;
		}
		m_Human_Head->Render(m_D3D->GetDeviceContext());
		// Render the model using the light shader.
		result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Human_Head->GetIndexCount(), HumanHead* sumAllMovement* worldMatrix, viewMatrix, projectionMatrix,
			m_Human_Head->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
		if (!result)
		{
			return false;
		}

		m_Human_Body->Render(m_D3D->GetDeviceContext());
		// Render the model using the light shader.
		result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Human_Body->GetIndexCount(), HumanBody* sumAllMovement* worldMatrix, viewMatrix, projectionMatrix,
			m_Human_Body->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
		if (!result)
		{
			return false;
		}

		m_Human_Left_Leg->Render(m_D3D->GetDeviceContext());
		// Render the model using the light shader.
		result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Human_Left_Leg->GetIndexCount(), HumanLeftLeg* sumAllMovement*worldMatrix, viewMatrix, projectionMatrix,
			m_Human_Left_Leg->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
		if (!result)
		{
			return false;
		}

		m_Human_Left_Arm->Render(m_D3D->GetDeviceContext());
		// Render the model using the light shader.
		result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Human_Left_Arm->GetIndexCount(), HumanLeftArm* sumAllMovement* worldMatrix, viewMatrix, projectionMatrix,
			m_Human_Left_Arm->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
		if (!result)
		{
			return false;
		}

		if (stage == 1) {
			D3DXMATRIX UpDownObstacle;

			D3DXMATRIX Shoot_bullet;
			D3DXMATRIX Shoot_bullet_1stMove;
			D3DXMATRIX Shoot_bullet_2ndMove;
			D3DXMATRIX Map_1stMove;
			D3DXMATRIX Map_2ndMove;
			//////////////////////////////////////////////////////////////0621 지명근 행렬 추가 시작 //////////
			D3DXMATRIX Shoot_bullet_3rdMove;
			D3DXMATRIX Shoot_bullet_leftmap_no1;
			D3DXMATRIX Shoot_bullet_leftmap_no2;
			D3DXMATRIX Shoot_bullet_leftmap_no3;
			D3DXMATRIX Shoot_bullet_leftmap_no4;
			D3DXMATRIX Shoot_bullet_leftmap_no5;
			D3DXMATRIX Shoot_bullet_leftmap_no6;
			D3DXMATRIX Shoot_bullet_leftmap_no7;
			D3DXMATRIX Shoot_bullet_rightmap_no1;
			D3DXMATRIX Shoot_bullet_rightmap_no2;
			D3DXMATRIX Shoot_bullet_rightmap_no3;
			D3DXMATRIX Shoot_bullet_rightmap_no4;
			D3DXMATRIX Shoot_bullet_rightmap_no5;
			D3DXMATRIX Map_LeftFinish;
			D3DXMATRIX Map_RightFinish;
			//////////////////////////////////////////////////////////////0621 지명근 행렬 추가 끝 ////////////

			D3DXMatrixScaling(&Shoot_bullet, 0.2f, 0.2f, 0.2f);
			D3DXMatrixScaling(&Shoot_bullet_1stMove, 0.3f, 0.3f, 0.3f);
			D3DXMatrixScaling(&Shoot_bullet_2ndMove, 0.3f, 0.3f, 0.3f);
			D3DXMatrixScaling(&UpDownObstacle, 1.0f, 0.2f, 2.0f);
			/////////////////////////////////////////////////////////0621 지명근 스케일링 추가 시작  //////
			D3DXMatrixScaling(&Shoot_bullet_3rdMove, 0.3f, 0.3f, 0.3f);
			D3DXMatrixScaling(&Shoot_bullet_leftmap_no1, 0.2f, 0.2f, 0.2f);
			D3DXMatrixScaling(&Shoot_bullet_leftmap_no2, 0.2f, 0.2f, 0.2f);
			D3DXMatrixScaling(&Shoot_bullet_leftmap_no3, 0.2f, 0.2f, 0.2f);
			D3DXMatrixScaling(&Shoot_bullet_leftmap_no4, 0.2f, 0.2f, 0.2f);
			D3DXMatrixScaling(&Shoot_bullet_leftmap_no5, 0.2f, 0.2f, 0.2f);
			D3DXMatrixScaling(&Shoot_bullet_leftmap_no6, 0.2f, 0.2f, 0.2f);
			D3DXMatrixScaling(&Shoot_bullet_leftmap_no7, 0.2f, 0.2f, 0.2f);
			D3DXMatrixScaling(&Shoot_bullet_rightmap_no1, 0.2f, 0.2f, 0.2f);
			D3DXMatrixScaling(&Shoot_bullet_rightmap_no2, 0.2f, 0.2f, 0.2f);
			D3DXMatrixScaling(&Shoot_bullet_rightmap_no3, 0.2f, 0.2f, 0.2f);
			D3DXMatrixScaling(&Shoot_bullet_rightmap_no4, 0.2f, 0.2f, 0.2f);
			D3DXMatrixScaling(&Shoot_bullet_rightmap_no5, 0.2f, 0.2f, 0.2f);
			D3DXMatrixScaling(&Map_LeftFinish, 5.0f, 0.3f, 5.0f);
			D3DXMatrixScaling(&Map_RightFinish, 5.0f, 0.3f, 5.0f);
			/////////////////////////////////////////////////////////0621 지명근 스케일링 추가   끝////////////

			///////////////////////////////////////////////////////////추가   끝  by 지명근//////

			D3DXMatrixTranslation(&temp, 13.0f + 5 * sin(t*XM_PI / 16), 4.0f, 40.5f + 15 * sin(t*XM_PI / 16));
			Map_1stMove *= temp;

			D3DXMatrixTranslation(&temp, -15.0f + 5 * sin(t*XM_PI / 16), 1.0f, 30.5f - 10 * sin(t*XM_PI / 16));
			Map_2ndMove *= temp;

			D3DXMatrixTranslation(&temp, 13.0f + 5 * sin(t*XM_PI / 16), 4.0f, 35.5f + 15 * sin(t*XM_PI / 16));
			Map_LeftFinish *= temp;
			D3DXMatrixTranslation(&temp, -15.0f + 5 * sin(t*XM_PI / 16), 1.0f, 45.5f - 10 * sin(t*XM_PI / 16));
			Map_RightFinish *= temp;




			D3DXMatrixScaling(&Map, 10.0f, 0.3f, 40.0f);

			//////////////////////////////////////////////////테스트 추락   끝  by 지명근///////
			D3DXMatrixTranslation(&temp, 0.0f, -2.7f, 0.0f);
			Map *= temp;


			//////////////////////////////////////////0620 김형륙 시간 추가시작

			///////////////////////////////////////////////////////////////////////////////////////////점프구현부분////
			////////////////////////////점프를 눌러서 높이가 이미 최대치에 도달한 이후 << //////
			if (checkJump == false && jumppress == 0.0f) {
				if (testjumpfloat > 0.0f) ///////////아직 높이가 0보다 높은 체공중일때
					if (testjumpfloat > 0.3f) { testjumpfloat *= 0.92f; } //////////일정 높이보다 높으면 0.92씩 곱해서 약간 작아지게
					else testjumpfloat -= 0.1f; /////일정높이보다 낮으면 땅에 거의 다 떨어졌으니 팍 떨어지게
					D3DXMatrixTranslation(&move, 0.0f, 0.0f + testjumpfloat, x); ////매 높이값의 변화만큼 위치를 이동(떨어지는 형식)
					if (testjumpfloat < 0.0f) //////// 높이값이 0보다 작아져 버리는, 이미 땅에 도달한 후라면
						jumpposition = 0.0f; ///////// 점프포지션이라는, 점프후 최고점을 찍고 내려오는지를 체크하던 변수를 다시 디폴트로 설정
			}
			/////////////////////////////점프를 눌러서 높이가 아직 최대치에 도달하지 않은, 점프해서 올라가는 중이라면
			else if (checkJump == true || (jumppress == 1.0f && jumpposition == 0.0f)) {
				if (testjumpfloat < 4.4f) { //////점프력의 최대치에 도달하지 않았을 때 
					if (testjumpfloat < 0.4f) { testjumpfloat += 0.1f; } ///////처음엔 약간 적은 속도로
					else testjumpfloat += 0.2f; //////이후엔 일정한 가속도로 올라갑니다.
				}
				else if (testjumpfloat >= 4.4f) { ////점프력의 최대치에 도달했을 때 
					jumpposition = 1.0f; //////점프후 최고점에 도달했다는 정보를 갱신해줘서 점프를(스페이스바를) 눌러도 점프상태로 처리하지 않도록 합니다.
					jumppress = 0.0f;    //////점프후 점프를 유지하기 위한 조건변수도 디폴트로 갱신합니다.
				}
				///////////////////마찬가지로 높이가 올라가는 순간순간마다 변화하는 높이값에 맞춰서 새로 트렌슬레이션 해줍니다.
				D3DXMatrixTranslation(&move, 0.0f, testjumpfloat, x);

			}
			sumAllMovement._42 += move._42;

			//////////////////////////////////////////0620 김형륙 시간 추가끝
			D3DXMatrixTranslation(&temp, 0.0f, -3.0f, 0.0f);
			worldMatrix *= temp;
			// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
			m_Map->Render(m_D3D->GetDeviceContext());
			// Render the model using the light shader.
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Map->GetIndexCount(), Map*worldMatrix, viewMatrix, projectionMatrix,
				m_Map->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}


			D3DXMatrixTranslation(&temp, -5.0f + 1.2*second, 0.2f, 4.0f);
			Shoot_bullet *= temp;

			/////////////////////////////////////////////////////////////오른쪽 위에 나오는 움직이는 총알  
			D3DXMatrixTranslation(&temp, 5.0f + 5 * sin(t*XM_PI / 16) + 5 * second, 5.5f, 40.5f + 15 * sin(t*XM_PI / 16));
			Shoot_bullet_1stMove *= temp;

			D3DXMatrixTranslation(&temp, 5.0f + 5 * sin(t*XM_PI / 16) + second, 5.0f, 25.5f + 15 * sin(t*XM_PI / 16));
			Shoot_bullet_rightmap_no1 *= temp;

			D3DXMatrixTranslation(&temp, 5.0f + 5 * sin(t*XM_PI / 16) + 2 * second, 6.5f, 35.5f + 15 * sin(t*XM_PI / 16));
			Shoot_bullet_rightmap_no2 *= temp;

			D3DXMatrixTranslation(&temp, 5.0f + 5 * sin(t*XM_PI / 16) + 2 * second, 6.0f, 30.5f + 15 * sin(t*XM_PI / 16));
			Shoot_bullet_rightmap_no3 *= temp;

			D3DXMatrixTranslation(&temp, 5.0f + 5 * sin(t*XM_PI / 16) + 5 * second, 4.5f, 60.5f + 15 * sin(t*XM_PI / 16));
			Shoot_bullet_rightmap_no4 *= temp;

			D3DXMatrixTranslation(&temp, 5.0f + 5 * sin(t*XM_PI / 16) + second, 7.5f, 40.5f + 15 * sin(t*XM_PI / 16));
			Shoot_bullet_rightmap_no5 *= temp;

			/////////////////////////////////////////////////////////////왼쪽 위에 나오는 움직이는 총알  
			D3DXMatrixTranslation(&temp, -14.0f + 5 * sin(t*XM_PI / 16), 23.5f - 2 * second, 27.5f - 10 * sin(t*XM_PI / 16));
			Shoot_bullet_2ndMove *= temp;

			D3DXMatrixTranslation(&temp, -10.0f + 5 * sin(t*XM_PI / 16), 12.5f - second, 30.5f - 10 * sin(t*XM_PI / 16));
			Shoot_bullet_3rdMove *= temp;

			D3DXMatrixTranslation(&temp, -18.0f + 5 * sin(t*XM_PI / 16), 10.5f - 0.8*second, 24.5f - 10 * sin(t*XM_PI / 16));
			Shoot_bullet_leftmap_no1 *= temp;

			D3DXMatrixTranslation(&temp, -14.0f + 5 * sin(t*XM_PI / 16), 14.5f - second, 30.5f - 10 * sin(t*XM_PI / 16));
			Shoot_bullet_leftmap_no2 *= temp;

			D3DXMatrixTranslation(&temp, -18.0f + 5 * sin(t*XM_PI / 16), 8.5f - 0.5*second, 27.5f - 10 * sin(t*XM_PI / 16));
			Shoot_bullet_leftmap_no3 *= temp;

			D3DXMatrixTranslation(&temp, -16.0f + 5 * sin(t*XM_PI / 16), 14.5f - 1.2*second, 25.5f - 10 * sin(t*XM_PI / 16));
			Shoot_bullet_leftmap_no4 *= temp;

			D3DXMatrixTranslation(&temp, -18.0f + 5 * sin(t*XM_PI / 16), 10.5f - second, 27.5f - 10 * sin(t*XM_PI / 16));
			Shoot_bullet_leftmap_no5 *= temp;

			D3DXMatrixTranslation(&temp, -12.0f + 5 * sin(t*XM_PI / 16), 13.5f - 1.3*second, 26.5f - 10 * sin(t*XM_PI / 16));
			Shoot_bullet_leftmap_no6 *= temp;

			D3DXMatrixTranslation(&temp, -15.0f + 5 * sin(t*XM_PI / 16), 7.5f - 0.3*second, 28.5f - 10 * sin(t*XM_PI / 16));
			Shoot_bullet_leftmap_no7 *= temp;

			D3DXMatrixTranslation(&temp, 0.0f, 0.0f - 8 * sin(t*XM_PI / 16), 10.0f);
			UpDownObstacle *= temp;

			m_Shoot_bullet->Render(m_D3D->GetDeviceContext());
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Shoot_bullet->GetIndexCount(), Shoot_bullet* worldMatrix, viewMatrix, projectionMatrix,
				m_Shoot_bullet->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			m_Shoot_bullet_1stMove->Render(m_D3D->GetDeviceContext());
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Shoot_bullet_1stMove->GetIndexCount(), Shoot_bullet_1stMove* worldMatrix, viewMatrix, projectionMatrix,
				m_Shoot_bullet_1stMove->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			m_Shoot_bullet_2ndMove->Render(m_D3D->GetDeviceContext());
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Shoot_bullet_2ndMove->GetIndexCount(), Shoot_bullet_2ndMove* worldMatrix, viewMatrix, projectionMatrix,
				m_Shoot_bullet_2ndMove->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			m_Map_1stMove->Render(m_D3D->GetDeviceContext());
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Map_1stMove->GetIndexCount(), Map_1stMove*worldMatrix, viewMatrix, projectionMatrix,
				m_Map_1stMove->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			m_Map_2ndMove->Render(m_D3D->GetDeviceContext());
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Map_2ndMove->GetIndexCount(), Map_2ndMove*worldMatrix, viewMatrix, projectionMatrix,
				m_Map_2ndMove->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			m_Map_LeftFinish->Render(m_D3D->GetDeviceContext());
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Map_LeftFinish->GetIndexCount(), Map_LeftFinish*worldMatrix, viewMatrix, projectionMatrix,
				m_Map_LeftFinish->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			m_Map_RightFinish->Render(m_D3D->GetDeviceContext());
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Map_RightFinish->GetIndexCount(), Map_RightFinish*worldMatrix, viewMatrix, projectionMatrix,
				m_Map_RightFinish->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			m_UpDownObstaclee->Render(m_D3D->GetDeviceContext());
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_UpDownObstaclee->GetIndexCount(), UpDownObstacle*worldMatrix, viewMatrix, projectionMatrix,
				m_UpDownObstaclee->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			////////////////////////////////////////////////////////0621 지명근 렌더 추가 시작/////////////////
			m_Shoot_bullet_3rdMove->Render(m_D3D->GetDeviceContext());
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Shoot_bullet_3rdMove->GetIndexCount(), Shoot_bullet_3rdMove* worldMatrix, viewMatrix, projectionMatrix,
				m_Shoot_bullet_3rdMove->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			m_Shoot_bullet_leftmap_no1->Render(m_D3D->GetDeviceContext());
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Shoot_bullet_leftmap_no1->GetIndexCount(), Shoot_bullet_leftmap_no1* worldMatrix, viewMatrix, projectionMatrix,
				m_Shoot_bullet_leftmap_no1->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			m_Shoot_bullet_leftmap_no2->Render(m_D3D->GetDeviceContext());
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Shoot_bullet_leftmap_no2->GetIndexCount(), Shoot_bullet_leftmap_no2* worldMatrix, viewMatrix, projectionMatrix,
				m_Shoot_bullet_leftmap_no2->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			m_Shoot_bullet_leftmap_no3->Render(m_D3D->GetDeviceContext());
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Shoot_bullet_leftmap_no3->GetIndexCount(), Shoot_bullet_leftmap_no3* worldMatrix, viewMatrix, projectionMatrix,
				m_Shoot_bullet_leftmap_no3->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			m_Shoot_bullet_leftmap_no4->Render(m_D3D->GetDeviceContext());
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Shoot_bullet_leftmap_no4->GetIndexCount(), Shoot_bullet_leftmap_no4* worldMatrix, viewMatrix, projectionMatrix,
				m_Shoot_bullet_leftmap_no4->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			m_Shoot_bullet_leftmap_no5->Render(m_D3D->GetDeviceContext());
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Shoot_bullet_leftmap_no5->GetIndexCount(), Shoot_bullet_leftmap_no5* worldMatrix, viewMatrix, projectionMatrix,
				m_Shoot_bullet_leftmap_no5->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			m_Shoot_bullet_leftmap_no6->Render(m_D3D->GetDeviceContext());
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Shoot_bullet_leftmap_no6->GetIndexCount(), Shoot_bullet_leftmap_no6* worldMatrix, viewMatrix, projectionMatrix,
				m_Shoot_bullet_leftmap_no6->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			m_Shoot_bullet_leftmap_no7->Render(m_D3D->GetDeviceContext());
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Shoot_bullet_leftmap_no7->GetIndexCount(), Shoot_bullet_leftmap_no7* worldMatrix, viewMatrix, projectionMatrix,
				m_Shoot_bullet_leftmap_no7->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			m_Shoot_bullet_rightmap_no1->Render(m_D3D->GetDeviceContext());
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Shoot_bullet_rightmap_no1->GetIndexCount(), Shoot_bullet_rightmap_no1* worldMatrix, viewMatrix, projectionMatrix,
				m_Shoot_bullet_rightmap_no1->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			m_Shoot_bullet_rightmap_no2->Render(m_D3D->GetDeviceContext());
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Shoot_bullet_rightmap_no2->GetIndexCount(), Shoot_bullet_rightmap_no2* worldMatrix, viewMatrix, projectionMatrix,
				m_Shoot_bullet_rightmap_no2->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			m_Shoot_bullet_rightmap_no3->Render(m_D3D->GetDeviceContext());
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Shoot_bullet_rightmap_no3->GetIndexCount(), Shoot_bullet_rightmap_no3* worldMatrix, viewMatrix, projectionMatrix,
				m_Shoot_bullet_rightmap_no3->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			m_Shoot_bullet_rightmap_no4->Render(m_D3D->GetDeviceContext());
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Shoot_bullet_rightmap_no4->GetIndexCount(), Shoot_bullet_rightmap_no4* worldMatrix, viewMatrix, projectionMatrix,
				m_Shoot_bullet_rightmap_no4->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			m_Shoot_bullet_rightmap_no5->Render(m_D3D->GetDeviceContext());
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Shoot_bullet_rightmap_no5->GetIndexCount(), Shoot_bullet_rightmap_no5* worldMatrix, viewMatrix, projectionMatrix,
				m_Shoot_bullet_rightmap_no5->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			////////////////////////////////////////////////////////0621 지명근 렌더 추가 시작/////////////////
		}
		else if (stage == 2) {
			D3DXMATRIX UpDownObstacle[9];
			D3DXMATRIX RotObstacle[24];
			////////////////////////////////////0617 박민 행렬추가 끝//////////////////////////

			////////////////////////////////////0618 박민 행렬추가 시작////////////////////////
			D3DXMATRIX Map2;
			D3DXMATRIX Map3;
			D3DXMATRIX DynamicBoard[4];
			D3DXMATRIX Stage1background;
			////////////////////////////////////0618 박민 행렬추가 끝//////////////////////////

			bool checkMoveLeg = false;
			for (int i = 0; i < 9; i++)
				D3DXMatrixScaling(&UpDownObstacle[i], 1.5f, 0.2f, 2.0f);

			for (int i = 0; i < 24; i++)
				D3DXMatrixScaling(&RotObstacle[i], 1.5f, 0.2f, 2.0f);

			D3DXMatrixScaling(&Map2, 10.0f, 0.3f, 10.0f);
			D3DXMatrixScaling(&Map3, 10.0f, 0.3f, 7.0f);
			for (int i = 0; i < 4; i++)
				D3DXMatrixScaling(&DynamicBoard[i], 3.0f, 0.3f, 2.5f);

			D3DXMatrixScaling(&Map, 10.0f, 0.3f, 40.0f);
			D3DXMatrixTranslation(&temp, 0.0f, 2.0f, 0.0f);
			HumanHead *= temp;

			D3DXMatrixTranslation(&temp, 0.0f, -2.7f, 0.0f);
			Map *= temp;
			static float t2[9] = { 0, };
			static ULONGLONG timeStart2 = 0;
			ULONGLONG timeCur2 = GetTickCount64();
			if (timeStart2 == 0)
				timeStart2 = timeCur2;
			for (int i = 0; i < 9; i++)
			{

				t2[i] = (timeCur2 - timeStart2);

			}
			float UpdownZ1 = 45.0f;
			float UpdownZ2 = 50.0f;
			float UpdownZ3 = 55.0f;

			t2[0] /= 104.0f;
			t2[1] /= 95.0f;
			t2[2] /= 140.0f;
			t2[3] /= 80.0f;
			t2[4] /= 115.0f;
			t2[5] /= 90.0f;
			t2[6] /= 132.0f;
			t2[7] /= 110.0f;
			t2[8] /= 99.0f;
			if ((int)t2[0] % 16 < 8.0f)//1
			{
				offset[0] = t2[0] - offset[1];
				D3DXMatrixTranslation(&temp, -5.0f, offset[0], UpdownZ1);
				UpDownObstacle[0] *= temp;
				offset[0] = t2[0];
			}
			else if (((int)t2[0] % 16) >= 8.0f && (int)t2[0] % 16 < 16.0f)
			{
				offset[1] = t2[0] - offset[0];
				D3DXMatrixTranslation(&temp, -5.0f, 8.0f - offset[1], UpdownZ1);
				UpDownObstacle[0] *= temp;
				offset[1] = t2[0];
			}

			if ((int)t2[1] % 16 < 8.0f)//2
			{
				offset[2] = t2[1] - offset[3];
				D3DXMatrixTranslation(&temp, 0.0f, offset[2], UpdownZ1);
				UpDownObstacle[1] *= temp;
				offset[2] = t2[1];
			}
			else if (((int)t2[1] % 16) >= 8.0f && (int)t2[1] % 16 < 16.0f)
			{
				offset[3] = t2[1] - offset[2];
				D3DXMatrixTranslation(&temp, 0.0f, 8.0f - offset[3], UpdownZ1);
				UpDownObstacle[1] *= temp;
				offset[3] = t2[1];
			}


			if ((int)t2[2] % 16 < 8.0f)//3
			{
				offset[4] = t2[2] - offset[5];
				D3DXMatrixTranslation(&temp, 5.0f, offset[4], UpdownZ1);
				UpDownObstacle[2] *= temp;
				offset[4] = t2[2];
			}
			else if (((int)t2[2] % 16) >= 8.0f && (int)t2[2] % 16 < 16.0f)
			{
				offset[5] = t2[2] - offset[4];
				D3DXMatrixTranslation(&temp, 5.0f, 8.0f - offset[5], UpdownZ1);
				UpDownObstacle[2] *= temp;
				offset[5] = t2[2];
			}


			if ((int)t2[3] % 16 < 8.0f)//4
			{
				offset[6] = t2[3] - offset[7];
				D3DXMatrixTranslation(&temp, -5.0f, offset[6], UpdownZ2);
				UpDownObstacle[3] *= temp;
				offset[6] = t2[3];
			}
			else if (((int)t2[3] % 16) >= 8.0f && (int)t2[3] % 16 < 16.0f)
			{
				offset[7] = t2[3] - offset[6];
				D3DXMatrixTranslation(&temp, -5.0f, 8.0f - offset[7], UpdownZ2);
				UpDownObstacle[3] *= temp;
				offset[7] = t2[3];
			}


			if ((int)t2[4] % 16 < 8.0f)//5
			{
				offset[8] = t2[4] - offset[9];
				D3DXMatrixTranslation(&temp, 0.0f, offset[8], UpdownZ2);
				UpDownObstacle[4] *= temp;
				offset[8] = t2[4];
			}
			else if (((int)t2[4] % 16) >= 8.0f && (int)t2[4] % 16 < 16.0f)
			{
				offset[9] = t2[4] - offset[8];
				D3DXMatrixTranslation(&temp, 0.0f, 8.0f - offset[9], UpdownZ2);
				UpDownObstacle[4] *= temp;
				offset[9] = t2[4];
			}

			if ((int)t2[5] % 16 < 8.0f)//6
			{
				offset[10] = t2[5] - offset[11];
				D3DXMatrixTranslation(&temp, 5.0f, offset[10], UpdownZ2);
				UpDownObstacle[5] *= temp;
				offset[10] = t2[5];
			}
			else if (((int)t2[5] % 16) >= 8.0f && (int)t2[5] % 16 < 16.0f)
			{
				offset[11] = t2[5] - offset[10];
				D3DXMatrixTranslation(&temp, 5.0f, 8.0f - offset[11], UpdownZ2);
				UpDownObstacle[5] *= temp;
				offset[11] = t2[5];
			}

			if ((int)t2[6] % 16 < 8.0f)//7
			{
				offset[12] = t2[6] - offset[13];
				D3DXMatrixTranslation(&temp, -5.0f, offset[12], UpdownZ3);
				UpDownObstacle[6] *= temp;
				offset[12] = t2[6];
			}
			else if (((int)t2[6] % 16) >= 8.0f && (int)t2[6] % 16 < 16.0f)
			{
				offset[13] = t2[6] - offset[12];
				D3DXMatrixTranslation(&temp, -5.0f, 8.0f - offset[13], UpdownZ3);
				UpDownObstacle[6] *= temp;
				offset[13] = t2[6];
			}

			if ((int)t2[7] % 16 < 8.0f)//8
			{
				offset[14] = t2[7] - offset[15];
				D3DXMatrixTranslation(&temp, 0.0f, offset[14], UpdownZ3);
				UpDownObstacle[7] *= temp;
				offset[14] = t2[7];
			}
			else if (((int)t2[7] % 16) >= 8.0f && (int)t2[7] % 16 < 16.0f)
			{
				offset[15] = t2[7] - offset[14];
				D3DXMatrixTranslation(&temp, 0.0f, 8.0f - offset[15], UpdownZ3);
				UpDownObstacle[7] *= temp;
				offset[15] = t2[7];
			}

			if ((int)t2[8] % 16 < 8.0f)//9
			{
				offset[16] = t2[8] - offset[17];
				D3DXMatrixTranslation(&temp, 5.0f, offset[16], UpdownZ3);
				UpDownObstacle[8] *= temp;
				offset[16] = t2[8];
			}
			else if (((int)t2[8] % 16) >= 8.0f && (int)t2[8] % 16 < 16.0f)
			{
				offset[17] = t2[8] - offset[16];
				D3DXMatrixTranslation(&temp, 5.0f, 8.0f - offset[17], UpdownZ3);
				UpDownObstacle[8] *= temp;
				offset[17] = t2[8];
			}

			/////////////RotObstacle 1~24 움직임 정의 시작/////////////
			float RotObY = 4.0f;
			float RotObZ1 = 0.0f;
			float RotObZ2 = 5.0f;
			float RotObZ3 = 10.0f;
			float RotObZ4 = 15.0f;
			RotObY += 8.0f;
			RotObZ1 += 85.0f;
			RotObZ2 += 85.0f;
			RotObZ3 += 85.0f;
			RotObZ4 += 85.0f;


			D3DXMatrixTranslation(&temp, 0.0f, RotObY, RotObZ1);
			RotObstacle[0] *= temp;
			D3DXMatrixRotationZ(&temp, -t);
			RotObstacle[0] *= temp;
			D3DXMatrixTranslation(&temp, 0.0f, 3.0f, 0.0f);
			RotObstacle[0] *= temp;
			D3DXMatrixRotationZ(&temp, t);
			RotObstacle[0] *= temp;

			D3DXMatrixTranslation(&temp, 0.0f, RotObY, RotObZ1);
			RotObstacle[1] *= temp;
			D3DXMatrixRotationZ(&temp, -t);
			RotObstacle[1] *= temp;
			D3DXMatrixTranslation(&temp, 0.0f, -3.0f, 0.0f);
			RotObstacle[1] *= temp;
			D3DXMatrixRotationZ(&temp, t);
			RotObstacle[1] *= temp;

			D3DXMatrixTranslation(&temp, 0.0f, RotObY, RotObZ1);
			RotObstacle[2] *= temp;
			D3DXMatrixRotationZ(&temp, -t);
			RotObstacle[2] *= temp;
			D3DXMatrixTranslation(&temp, -3.0f, 0.0f, 0.0f);
			RotObstacle[2] *= temp;
			D3DXMatrixRotationZ(&temp, t);
			RotObstacle[2] *= temp;

			D3DXMatrixTranslation(&temp, 0.0f, RotObY, RotObZ1);
			RotObstacle[3] *= temp;
			D3DXMatrixRotationZ(&temp, -t);
			RotObstacle[3] *= temp;
			D3DXMatrixTranslation(&temp, 3.0f, 0.0f, 0.0f);
			RotObstacle[3] *= temp;
			D3DXMatrixRotationZ(&temp, t);
			RotObstacle[3] *= temp;

			D3DXMatrixTranslation(&temp, 0.0f, RotObY, RotObZ2);
			RotObstacle[4] *= temp;
			D3DXMatrixRotationZ(&temp, t);
			RotObstacle[4] *= temp;
			D3DXMatrixTranslation(&temp, 0.0f, 5.0f, 0.0f);
			RotObstacle[4] *= temp;
			D3DXMatrixRotationZ(&temp, -t);
			RotObstacle[4] *= temp;

			D3DXMatrixTranslation(&temp, 0.0f, RotObY, RotObZ2);
			RotObstacle[5] *= temp;
			D3DXMatrixRotationZ(&temp, t);
			RotObstacle[5] *= temp;
			D3DXMatrixTranslation(&temp, 0.0f, -5.0f, 0.0f);
			RotObstacle[5] *= temp;
			D3DXMatrixRotationZ(&temp, -t);
			RotObstacle[5] *= temp;

			D3DXMatrixTranslation(&temp, 0.0f, RotObY, RotObZ2);
			RotObstacle[6] *= temp;
			D3DXMatrixRotationZ(&temp, t);
			RotObstacle[6] *= temp;
			D3DXMatrixTranslation(&temp, 5.0f, 0.0f, 0.0f);
			RotObstacle[6] *= temp;
			D3DXMatrixRotationZ(&temp, -t);
			RotObstacle[6] *= temp;

			D3DXMatrixTranslation(&temp, 0.0f, RotObY, RotObZ2);
			RotObstacle[7] *= temp;
			D3DXMatrixRotationZ(&temp, t);
			RotObstacle[7] *= temp;
			D3DXMatrixTranslation(&temp, -5.0f, 0.0f, 0.0f);
			RotObstacle[7] *= temp;
			D3DXMatrixRotationZ(&temp, -t);
			RotObstacle[7] *= temp;

			D3DXMatrixTranslation(&temp, 0.0f, RotObY, RotObZ2);
			RotObstacle[8] *= temp;
			D3DXMatrixRotationZ(&temp, t);
			RotObstacle[8] *= temp;
			D3DXMatrixTranslation(&temp, -5.0f, 5.0f, 0.0f);
			RotObstacle[8] *= temp;
			D3DXMatrixRotationZ(&temp, -t);
			RotObstacle[8] *= temp;

			D3DXMatrixTranslation(&temp, 0.0f, RotObY, RotObZ2);
			RotObstacle[9] *= temp;
			D3DXMatrixRotationZ(&temp, t);
			RotObstacle[9] *= temp;
			D3DXMatrixTranslation(&temp, 5.0f, -5.0f, 0.0f);
			RotObstacle[9] *= temp;
			D3DXMatrixRotationZ(&temp, -t);
			RotObstacle[9] *= temp;

			D3DXMatrixTranslation(&temp, 0.0f, RotObY, RotObZ2);
			RotObstacle[10] *= temp;
			D3DXMatrixRotationZ(&temp, t);
			RotObstacle[10] *= temp;
			D3DXMatrixTranslation(&temp, -5.0f, -5.0f, 0.0f);
			RotObstacle[10] *= temp;
			D3DXMatrixRotationZ(&temp, -t);
			RotObstacle[10] *= temp;

			D3DXMatrixTranslation(&temp, 0.0f, RotObY, RotObZ2);
			RotObstacle[11] *= temp;
			D3DXMatrixRotationZ(&temp, t);
			RotObstacle[11] *= temp;
			D3DXMatrixTranslation(&temp, 5.0f, 5.0f, 0.0f);
			RotObstacle[11] *= temp;
			D3DXMatrixRotationZ(&temp, -t);
			RotObstacle[11] *= temp;


			D3DXMatrixTranslation(&temp, 0.0f, RotObY, RotObZ3);
			RotObstacle[12] *= temp;
			D3DXMatrixRotationZ(&temp, -t);
			RotObstacle[12] *= temp;
			D3DXMatrixTranslation(&temp, 0.0f, 5.0f, 0.0f);
			RotObstacle[12] *= temp;
			D3DXMatrixRotationZ(&temp, t);
			RotObstacle[12] *= temp;

			D3DXMatrixTranslation(&temp, 0.0f, RotObY, RotObZ3);
			RotObstacle[13] *= temp;
			D3DXMatrixRotationZ(&temp, -t);
			RotObstacle[13] *= temp;
			D3DXMatrixTranslation(&temp, 0.0f, -5.0f, 0.0f);
			RotObstacle[13] *= temp;
			D3DXMatrixRotationZ(&temp, t);
			RotObstacle[13] *= temp;

			D3DXMatrixTranslation(&temp, 0.0f, RotObY, RotObZ3);
			RotObstacle[14] *= temp;
			D3DXMatrixRotationZ(&temp, -t);
			RotObstacle[14] *= temp;
			D3DXMatrixTranslation(&temp, 5.0f, 0.0f, 0.0f);
			RotObstacle[14] *= temp;
			D3DXMatrixRotationZ(&temp, t);
			RotObstacle[14] *= temp;

			D3DXMatrixTranslation(&temp, 0.0f, RotObY, RotObZ3);
			RotObstacle[15] *= temp;
			D3DXMatrixRotationZ(&temp, -t);
			RotObstacle[15] *= temp;
			D3DXMatrixTranslation(&temp, -5.0f, 0.0f, 0.0f);
			RotObstacle[15] *= temp;
			D3DXMatrixRotationZ(&temp, t);
			RotObstacle[15] *= temp;

			D3DXMatrixTranslation(&temp, 0.0f, RotObY, RotObZ3);
			RotObstacle[16] *= temp;
			D3DXMatrixRotationZ(&temp, -t);
			RotObstacle[16] *= temp;
			D3DXMatrixTranslation(&temp, -5.0f, 5.0f, 0.0f);
			RotObstacle[16] *= temp;
			D3DXMatrixRotationZ(&temp, t);
			RotObstacle[16] *= temp;

			D3DXMatrixTranslation(&temp, 0.0f, RotObY, RotObZ3);
			RotObstacle[17] *= temp;
			D3DXMatrixRotationZ(&temp, -t);
			RotObstacle[17] *= temp;
			D3DXMatrixTranslation(&temp, 5.0f, -5.0f, 0.0f);
			RotObstacle[17] *= temp;
			D3DXMatrixRotationZ(&temp, t);
			RotObstacle[17] *= temp;

			D3DXMatrixTranslation(&temp, 0.0f, RotObY, RotObZ3);
			RotObstacle[18] *= temp;
			D3DXMatrixRotationZ(&temp, -t);
			RotObstacle[18] *= temp;
			D3DXMatrixTranslation(&temp, -5.0f, -5.0f, 0.0f);
			RotObstacle[18] *= temp;
			D3DXMatrixRotationZ(&temp, t);
			RotObstacle[18] *= temp;

			D3DXMatrixTranslation(&temp, 0.0f, RotObY, RotObZ3);
			RotObstacle[19] *= temp;
			D3DXMatrixRotationZ(&temp, -t);
			RotObstacle[19] *= temp;
			D3DXMatrixTranslation(&temp, 5.0f, 5.0f, 0.0f);
			RotObstacle[19] *= temp;
			D3DXMatrixRotationZ(&temp, t);
			RotObstacle[19] *= temp;

			D3DXMatrixTranslation(&temp, 0.0f, RotObY, RotObZ4);
			RotObstacle[20] *= temp;
			D3DXMatrixRotationZ(&temp, t);
			RotObstacle[20] *= temp;
			D3DXMatrixTranslation(&temp, 0.0f, 3.0f, 0.0f);
			RotObstacle[20] *= temp;
			D3DXMatrixRotationZ(&temp, -t);
			RotObstacle[20] *= temp;

			D3DXMatrixTranslation(&temp, 0.0f, RotObY, RotObZ4);
			RotObstacle[21] *= temp;
			D3DXMatrixRotationZ(&temp, t);
			RotObstacle[21] *= temp;
			D3DXMatrixTranslation(&temp, 0.0f, -3.0f, 0.0f);
			RotObstacle[21] *= temp;
			D3DXMatrixRotationZ(&temp, -t);
			RotObstacle[21] *= temp;

			D3DXMatrixTranslation(&temp, 0.0f, RotObY, RotObZ4);
			RotObstacle[22] *= temp;
			D3DXMatrixRotationZ(&temp, t);
			RotObstacle[22] *= temp;
			D3DXMatrixTranslation(&temp, -3.0f, 0.0f, 0.0f);
			RotObstacle[22] *= temp;
			D3DXMatrixRotationZ(&temp, -t);
			RotObstacle[22] *= temp;

			D3DXMatrixTranslation(&temp, 0.0f, RotObY, RotObZ4);
			RotObstacle[23] *= temp;
			D3DXMatrixRotationZ(&temp, t);
			RotObstacle[23] *= temp;
			D3DXMatrixTranslation(&temp, 3.0f, 0.0f, 0.0f);
			RotObstacle[23] *= temp;
			D3DXMatrixRotationZ(&temp, -t);
			RotObstacle[23] *= temp;

			D3DXMatrixTranslation(&temp, 0.0f, 8.0f, 70.0f);
			Map2 *= temp;
			D3DXMatrixTranslation(&temp, 0.0f, 2.5f, 135.0f);
			Map3 *= temp;


			static float t3[4] = { 0, };
			static ULONGLONG timeStart3 = 0;
			ULONGLONG timeCur3 = GetTickCount64();
			if (timeStart3 == 0)
				timeStart3 = timeCur3;
			for (int i = 0; i < 4; i++)
			{

				t3[i] = (timeCur3 - timeStart3);

			}

			t3[0] /= 100.0f;
			t3[1] /= 100.0f;
			t3[2] /= 100.0f;
			t3[3] /= 100.0f;


			if ((int)t3[0] % 16 < 8.0f)//1
			{
				offset2[0] = t3[0] - offset2[1];
				D3DXMatrixTranslation(&temp, 4.0f - offset2[0], 6.5f, 105.0f);
				DynamicBoard[0] *= temp;
				offset2[0] = t3[0];
			}
			else if (((int)t3[0] % 16) >= 8.0f && (int)t3[0] % 16 < 16.0f)
			{
				offset2[1] = t3[0] - offset2[0];
				D3DXMatrixTranslation(&temp, offset2[1] - 4.0f, 6.5f, 105.0f);
				DynamicBoard[0] *= temp;
				offset2[1] = t3[0];
			}

			if ((int)t3[1] % 16 < 8.0f)//2
			{
				offset2[2] = t3[1] - offset2[3];
				D3DXMatrixTranslation(&temp, offset2[2] - 4.0f, 5.5f, 111.0f);
				DynamicBoard[1] *= temp;
				offset2[2] = t3[1];
			}
			else if (((int)t3[1] % 16) >= 8.0f && (int)t3[1] % 16 < 16.0f)
			{
				offset2[3] = t3[1] - offset2[2];
				D3DXMatrixTranslation(&temp, 4.0f - offset2[3], 5.5f, 111.0f);
				DynamicBoard[1] *= temp;
				offset2[3] = t3[1];
			}


			if ((int)t3[2] % 16 < 8.0f)//3
			{
				offset2[4] = t3[2] - offset2[5];
				D3DXMatrixTranslation(&temp, 4.0f - offset2[4], 4.5f, 117.0f);
				DynamicBoard[2] *= temp;
				offset2[4] = t3[2];
			}
			else if (((int)t3[2] % 16) >= 8.0f && (int)t3[2] % 16 < 16.0f)
			{
				offset2[5] = t3[2] - offset2[4];
				D3DXMatrixTranslation(&temp, offset2[5] - 4.0f, 4.5f, 117.0f);
				DynamicBoard[2] *= temp;
				offset2[5] = t3[2];
			}


			if ((int)t3[3] % 16 < 8.0f)//4
			{
				offset2[6] = t3[3] - offset2[7];
				D3DXMatrixTranslation(&temp, offset2[6] - 4.0f, 3.5f, 123.0f);
				DynamicBoard[3] *= temp;
				offset2[6] = t3[3];
			}
			else if (((int)t3[3] % 16) >= 8.0f && (int)t3[3] % 16 < 16.0f)
			{
				offset2[7] = t3[3] - offset2[6];
				D3DXMatrixTranslation(&temp, 4.0f - offset2[7], 3.5f, 123.0f);
				DynamicBoard[3] *= temp;
				offset2[7] = t3[3];
			}

			D3DXMatrixScaling(&Stage1background, 0.2f, 60.0f, 240.0f);
			D3DXMatrixTranslation(&temp, -60.0f, -10.7f, 175.0f);
			Stage1background *= temp;

			D3DXMatrixTranslation(&temp, 0.0f, -3.0f, 0.0f);
			worldMatrix *= temp;
			// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
			m_Map->Render(m_D3D->GetDeviceContext());
			// Render the model using the light shader.
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Map->GetIndexCount(), Map*worldMatrix, viewMatrix, projectionMatrix,
				m_Map->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
/*
			m_Camera->SetPosition(50.0f, 10.0f, -x);
			m_Camera->SetLookat(-30.0f, -5.0f, 5.0f);*/
			for (int i = 0; i < 9; i++)
			{

				m_UpDownObstacle[i]->Render(m_D3D->GetDeviceContext());
				// Render the model using the light shader.
				result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_UpDownObstacle[i]->GetIndexCount(), UpDownObstacle[i] * worldMatrix, viewMatrix, projectionMatrix,
					m_UpDownObstacle[i]->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());

				if (!result)
				{
					return false;
				}
			}

			for (int i = 0; i < 24; i++)
			{
				m_RotObstacle[i]->Render(m_D3D->GetDeviceContext());
				// Render the model using the light shader.
				result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_RotObstacle[i]->GetIndexCount(), RotObstacle[i] * worldMatrix, viewMatrix, projectionMatrix,
					m_RotObstacle[i]->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
				if (!result)
				{
					return false;
				}
			}
			m_Map2->Render(m_D3D->GetDeviceContext());
			// Render the model using the light shader.
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Map2->GetIndexCount(), Map2*worldMatrix, viewMatrix, projectionMatrix,
				m_Map2->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}
			m_Map3->Render(m_D3D->GetDeviceContext());
			// Render the model using the light shader.
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Map3->GetIndexCount(), Map3*worldMatrix, viewMatrix, projectionMatrix,
				m_Map3->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}

			for (int i = 0; i < 4; i++)
			{
				m_DynamicBoard[i]->Render(m_D3D->GetDeviceContext());
				// Render the model using the light shader.
				result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_DynamicBoard[i]->GetIndexCount(), DynamicBoard[i] * worldMatrix, viewMatrix, projectionMatrix,
					m_DynamicBoard[i]->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
				if (!result)
				{
					return false;
				}
			}
			m_Stage1background->Render(m_D3D->GetDeviceContext());
			// Render the model using the light shader.
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Stage1background->GetIndexCount(), Stage1background * worldMatrix, viewMatrix, projectionMatrix,
				m_Stage1background->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}


		}
		else if(stage == 3) {
			D3DXMATRIX Stage2Map[3];
			D3DXMATRIX Stage2background[4];
			D3DXMATRIX BBD;
			D3DXMATRIX AvoidObstacle[7];
			D3DXMATRIX BridgeObstacle[10];

			D3DXMatrixScaling(&Stage2Map[0], 10.0f, 0.3f, 20.0f);
			D3DXMatrixScaling(&Stage2Map[1], 10.0f, 0.3f, 17.0f);
			D3DXMatrixScaling(&Stage2Map[2], 10.0f, 0.3f, 10.0f);

			D3DXMatrixTranslation(&temp, 0.0f, -2.7f, 0.0f);
			Stage2Map[0] *= temp;
			D3DXMatrixTranslation(&temp, 0.0f, -2.7f, 73.0f);
			Stage2Map[1] *= temp;
			D3DXMatrixTranslation(&temp, 0.0f, -2.7f, 130.0f);
			Stage2Map[2] *= temp;

			for (int i = 0; i < 4; i++)
				D3DXMatrixScaling(&Stage2background[i], 0.2f, 60.0f, 240.0f);
			D3DXMatrixTranslation(&temp, -60.0f, -10.7f, 155.0f);
			Stage2background[0] *= temp;
			D3DXMatrixTranslation(&temp, -30.0f, -2.7f, 30.0f);
			Stage2background[1] *= temp;
			D3DXMatrixTranslation(&temp, -30.0f, -2.7f, 70.0f);
			Stage2background[2] *= temp;
			D3DXMatrixTranslation(&temp, -30.0f, -2.7f, 100.0f);
			Stage2background[3] *= temp;




			//장애물1
			for (int i = 0; i < 3; i++)
				D3DXMatrixScaling(&AvoidObstacle[i], 5.0f, 0.3f, 3.0f);

			for (int i = 3; i < 7; i++)
				D3DXMatrixScaling(&AvoidObstacle[i], 1.0f, 1.0f, 1.0f);

			float AvoidZ = 18.0f;
			D3DXMatrixTranslation(&temp, 5.0f, -2.7f, AvoidZ + 10.0f);
			AvoidObstacle[0] *= temp;
			D3DXMatrixTranslation(&temp, -5.0f, -2.7f, AvoidZ + 20.0f);
			AvoidObstacle[1] *= temp;
			D3DXMatrixTranslation(&temp, 5.0f, -2.7f, AvoidZ + 30.0f);
			AvoidObstacle[2] *= temp;


			D3DXMatrixTranslation(&temp, 0.0f, 10.0f, AvoidZ + 5.0f);
			AvoidObstacle[3] *= temp;
			D3DXMatrixRotationZ(&temp, XM_PI + XM_PI / 2 * sin(t));
			AvoidObstacle[3] *= temp;
			D3DXMatrixTranslation(&temp, 0.0f, 13.0f, 0.0f);
			AvoidObstacle[3] *= temp;

			D3DXMatrixTranslation(&temp, 0.0f, 10.0f, AvoidZ + 15.0f);
			AvoidObstacle[4] *= temp;
			D3DXMatrixRotationZ(&temp, XM_PI + XM_PI / 2 * sin(-t));
			AvoidObstacle[4] *= temp;
			D3DXMatrixTranslation(&temp, 0.0f, 13.0f, 0.0f);
			AvoidObstacle[4] *= temp;

			D3DXMatrixTranslation(&temp, 0.0f, 10.0f, AvoidZ + 25.0f);
			AvoidObstacle[5] *= temp;
			D3DXMatrixRotationZ(&temp, XM_PI + XM_PI / 2 * sin(t));
			AvoidObstacle[5] *= temp;
			D3DXMatrixTranslation(&temp, 0.0f, 13.0f, 0.0f);
			AvoidObstacle[5] *= temp;

			D3DXMatrixTranslation(&temp, 0.0f, 10.0f, AvoidZ + 35.0f);
			AvoidObstacle[6] *= temp;
			D3DXMatrixRotationZ(&temp, XM_PI + XM_PI / 2 * sin(-t));
			AvoidObstacle[6] *= temp;
			D3DXMatrixTranslation(&temp, 0.0f, 13.0f, 0.0f);
			AvoidObstacle[6] *= temp;


			//장애물2


			D3DXMatrixScaling(&BridgeObstacle[0], 1.4f, 0.3f, 4.0f);
			D3DXMatrixScaling(&BridgeObstacle[1], 6.2f, 0.3f, 1.4f);
			D3DXMatrixScaling(&BridgeObstacle[2], 1.4f, 0.3f, 4.0f);
			D3DXMatrixScaling(&BridgeObstacle[3], 6.2f, 0.3f, 1.4f);
			D3DXMatrixScaling(&BridgeObstacle[4], 1.4f, 0.3f, 4.0f);
			D3DXMatrixScaling(&BridgeObstacle[5], 6.2f, 0.3f, 1.4f);
			D3DXMatrixScaling(&BridgeObstacle[6], 1.4f, 0.3f, 4.0f);

			for (int i = 7; i < 10; i++)
				D3DXMatrixScaling(&BridgeObstacle[i], 1.0f, 1.0f, 1.0f);

			float BridgeZ = 94.0f;
			D3DXMatrixTranslation(&temp, -4.8f, -2.7f, BridgeZ);
			BridgeObstacle[0] *= temp;
			D3DXMatrixTranslation(&temp, 0.0f, -2.7f, BridgeZ + 5.4f);
			BridgeObstacle[1] *= temp;
			D3DXMatrixTranslation(&temp, 4.8f, -2.7f, BridgeZ + 10.8f);
			BridgeObstacle[2] *= temp;
			D3DXMatrixTranslation(&temp, 0.0f, -2.7f, BridgeZ + 16.2f);
			BridgeObstacle[3] *= temp;
			D3DXMatrixTranslation(&temp, -4.8f, -2.7f, BridgeZ + 21.4f);
			BridgeObstacle[4] *= temp;
			D3DXMatrixTranslation(&temp, 0.0f, -2.7f, BridgeZ + 26.8f);
			BridgeObstacle[5] *= temp;
			D3DXMatrixTranslation(&temp, 4.8f, -2.7f, BridgeZ + 32.2f);
			BridgeObstacle[6] *= temp;

			D3DXMatrixTranslation(&temp, 4.8f, 1.0f, BridgeZ + 11.0f);
			BridgeObstacle[7] *= temp;
			D3DXMatrixTranslation(&temp, -4.8f, 1.0f, BridgeZ + 21.2f);
			BridgeObstacle[8] *= temp;
			D3DXMatrixTranslation(&temp, 0.0f, 1.0f, BridgeZ + 16.2f);
			BridgeObstacle[9] *= temp;

			static float tt = 0;
			static ULONGLONG timeStart3 = 0;
			ULONGLONG timeCur3 = GetTickCount64();
			if (timeStart3 == 0)
				timeStart3 = timeCur3;

			tt = (timeCur3 - timeStart3) / 130.0f;


			if ((int)tt % 20< 10.0f)//1
			{
				offset3[0] = tt - offset3[1];
				D3DXMatrixTranslation(&temp, 5.0f - offset3[0], 0.0f, 0.0f);
				BridgeObstacle[7] *= temp;
				offset3[0] = tt;
			}
			else if (((int)tt % 20) >= 10.0f && (int)tt % 20< 20.0f)
			{
				offset3[1] = tt - offset3[0];
				D3DXMatrixTranslation(&temp, offset3[1] - 5.0f, 0.0f, 0.0f);
				BridgeObstacle[7] *= temp;
				offset3[1] = tt;
			}

			if ((int)tt % 20< 10.0f)//2
			{
				offset3[2] = tt - offset3[3];
				D3DXMatrixTranslation(&temp, offset3[2] - 5.0f, 0.0f, 0.0f);
				BridgeObstacle[8] *= temp;
				offset3[2] = tt;
			}
			else if (((int)tt % 20) >= 10.0f && (int)tt % 20< 20.0f)
			{
				offset3[3] = tt - offset3[2];
				D3DXMatrixTranslation(&temp, 5.0f - offset3[3], 0.0f, 0.0f);
				BridgeObstacle[8] *= temp;
				offset3[3] = tt;
			}

			tt = (timeCur3 - timeStart3) / 50.0f;
			if ((int)tt % 60< 30.0f)//3
			{
				offset3[4] = tt - offset3[5];
				D3DXMatrixTranslation(&temp, 0.0f, 0.0f, 15.0f - offset3[4]);
				BridgeObstacle[9] *= temp;
				offset3[4] = tt;
			}
			else if (((int)tt % 60) >= 30.0f && (int)tt % 60< 60.0f)
			{
				offset3[5] = tt - offset3[4];
				D3DXMatrixTranslation(&temp, 0.0f, 0.0f, offset3[5] - 15.0f);
				BridgeObstacle[9] *= temp;
				offset3[5] = tt;
			}

/*
			m_Camera->SetPosition(50.0f, 10.0f, -x);
			m_Camera->SetLookat(-30.0f, -5.0f, 5.0f);*/
			D3DXMatrixTranslation(&move, 0.0f, 0.0f, -x);
			D3DXMatrixRotationY(&rotate, left);
			sumAllMovement = (move*rotate);
			D3DXMatrixTranslation(&temp, 0.0f, -3.0f, 0.0f);
			worldMatrix *= temp;

			D3DXMatrixScaling(&BBD, 3.0f, 3.0f, 3.0f);

			D3DXMATRIX id;
			D3DXMatrixIdentity(&id);
			D3DXMatrixIdentity(&BBD); //빌보드 정의
			BBD._11 = viewMatrix._11;
			BBD._13 = viewMatrix._13;
			BBD._31 = viewMatrix._31;
			BBD._33 = viewMatrix._33;

			D3DXMatrixInverse(&BBD, NULL, &BBD);

			D3DXMatrixTranslation(&temp, -10.0f, 5.0f, 0.0f);
			BBD *= temp;

			for (int i = 0; i < 3; i++)
			{
				m_Stage2Map[i]->Render(m_D3D->GetDeviceContext());
				// Render the model using the light shader.
				result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Stage2Map[i]->GetIndexCount(), Stage2Map[i] * worldMatrix, viewMatrix, projectionMatrix,
					m_Stage2Map[i]->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
				if (!result)
				{
					return false;
				}
			}

			for (int i = 0; i < 4; i++)
			{
				m_Stage2background[0]->Render(m_D3D->GetDeviceContext());
				// Render the model using the light shader.
				result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Stage2background[0]->GetIndexCount(), Stage2background[0] * worldMatrix, viewMatrix, projectionMatrix,
					m_Stage2background[0]->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
				if (!result)
				{
					return false;
				}
			}
			m_BBD->Render(m_D3D->GetDeviceContext());
			// Render the model using the light shader.
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_BBD->GetIndexCount(), BBD * worldMatrix, id, projectionMatrix,
				m_BBD->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}


			for (int i = 0; i < 7; i++)
			{
				m_AvoidObstacle[i]->Render(m_D3D->GetDeviceContext());
				// Render the model using the light shader.
				result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_AvoidObstacle[i]->GetIndexCount(), AvoidObstacle[i] * worldMatrix, viewMatrix, projectionMatrix,
					m_AvoidObstacle[i]->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
				if (!result)
				{
					return false;
				}
			}
			for (int i = 0; i < 10; i++)
			{
				m_BridgeObstacle[i]->Render(m_D3D->GetDeviceContext());
				// Render the model using the light shader.
				result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_BridgeObstacle[i]->GetIndexCount(), BridgeObstacle[i] * worldMatrix, viewMatrix, projectionMatrix,
					m_BridgeObstacle[i]->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
				if (!result)
				{
					return false;
				}
			}
		}
		}
	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
}