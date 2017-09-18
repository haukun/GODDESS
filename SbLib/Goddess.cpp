/**
	@file		GoddessWindow.cpp
	@brief		GODDESS�E�B���h�E�N���X
	@author		Hau-kun
	@date		2014/10/12
	@version	0.1 Alpha
*/

#include "stdafx.h"
#include "UserHeader.h"
#include "UserMain.h"
#include "Goddess.h"
#include "config.h"

#include "MathUtil.h"

double** fewAlpha;				//	�A���t�@��������
int nPlotCnt = 0;				//	�v���b�g��


Goddess::Goddess(SbWindow* pWnd)
{
	Create(pWnd, pNowDisp->nWidth, pNowDisp->nHeight);

	fewAlpha = (double**)calloc(pNowDisp->nWidth, sizeof(double*));
	for(int x = 0; x < pNowDisp->nWidth; x++)
	{
		fewAlpha[x] = (double*)calloc(pNowDisp->nHeight, sizeof(double));
	}
	MathUtil::Srand();
}

Goddess::~Goddess(void)
{
	for(int x = 0; x < pNowDisp->nWidth; x++)
	{
		free(fewAlpha[x]);
	}
	free(fewAlpha);
}

HRESULT Goddess::Setup(SbSetupInfo* pInfo)
{
	//	�E�B���h�E�ړ�
	m_pWnd->MoveWindowCenter();

	//	�`��ݒ�
	SetRenderAlphaBlend(true);
    SetRenderAlphaBlendModeAddComposition();

	GetDevice()->SetRenderState(D3DRS_CLIPPING, FALSE);

	//	�e�N�X�`������
	m_pDotTex = new SbTex(this, "Library/Point.bmp", 1, 1);

	//	�ϐ�������
	m_nState = DRAW_STATE_SETUP;
	
	m_plot.Setup();

	return S_OK;
}

HRESULT Goddess::Execute(SbExecuteInfo* pInfo)
{
	BeginAct();

	switch(m_nState)
	{
	case DRAW_STATE_SETUP:
		Init();
		break;
	case DRAW_STATE_DRAW:
		Plot();
		break;
	case DRAW_STATE_SAVE:
		Save();
		break;
	case DRAW_STATE_FINISH:
		DestroyWindow(m_pWnd->GetWindowHandle());
		break;
	}

	EndAct();
	Flip();
	return S_OK;
}

//	������
void Goddess::Init(void)
{
	//	������Ԃ�0�ɏ�����
	for(int x = 0; x < pNowDisp->nWidth; x++)
	{
		for(int y = 0; y < pNowDisp->nHeight; y++)
		{
			fewAlpha[x][y] = 0;
		}
	}

	//	���W�_��1�ɃZ�b�g�B
	m_dX = 1, m_dY = 1, m_dZ = 1;

	//	��Ԃ�`���ԂɕύX
	m_nState = DRAW_STATE_DRAW;
}

//	�`��
void Goddess::Plot(void)
{
	char buff[20];
	int  hWidth = pNowDisp->nWidth / 2;
	int  hHeight = pNowDisp->nHeight / 2;

	for(int i = 0; i < PUT_PAR_FRAME; i++)
	{
		//HRESULT	hr = NULL;

		//	�p�����[�^�擾
		LogicParam param1(1, m_dX, m_dY, m_dZ);
		LogicParam param2(2, m_dX, m_dY, m_dZ);
		LogicParam param3(3, m_dX, m_dY, m_dZ);

		//	�p�����[�^����ɁA���W���v�Z
		double tx, ty, tz;
		tx = m_plot.Execute(&param1);
		ty = m_plot.Execute(&param2);
		tz = m_plot.Execute(&param3);

		//	���W����ʃT�C�Y�̍��W�ɕϊ�
		double dx, dy, dz;
		dx = tx;
		dy = ty;
		dz = tz;
		m_plot.PostExecute(&param1, &dx, &param2, &dy, &param3, &dz, nPlotCnt);
		dx = hWidth + (dx * pNowDisp->nRatio);
		dy = hHeight + (dy * pNowDisp->nRatio);
		dz = dz * 100;//RATIO;	//	MEMO 100�Œ�ɂ��Ȃ��ƐF���������B


		//	�_����ʓ��ɂ���Ε`��
		if(0 < dx && dx < pNowDisp->nWidth && 0 < dy && dy < pNowDisp->nHeight)
		{
			//	�A���t�@�̏����v�Z
			double drawAlpha = PUT_ALPHA * (pNowDisp->nRatio / 100.0) * (pNowDisp->nRatio / 100.0);
			double littleAlpha = drawAlpha - (int)drawAlpha;
			fewAlpha[(int)dx][(int)dy] += littleAlpha;

			//	�A���t�@����������1���z������`��ɓK�p
			if(fewAlpha[(int)dx][(int)dy] >= 1)
			{
				fewAlpha[(int)dx][(int)dy]--;
				drawAlpha++;
			}

			//	�`��
			if(drawAlpha >= 0)
			{
				D3DCOLOR col = HsvToRgb(drawAlpha, dz, 1, 1);
				//col = RgbToGray(2, col >> 16 & 0x00ff, col >> 8 & 0x00ff, col >> 0 & 0x00ff);

				m_pDotTex->Act(dx, dy, col);
			}
		}

		//	���W�̈����p��
		m_dX = tx;
		m_dY = ty;
		m_dZ = tz;

	}

	nPlotCnt++;

	sprintf(buff, "%06d", nPlotCnt);
	m_pWnd->SetTitle(buff);

	if(nPlotCnt >= FRAME_COUNT){
		m_nState = DRAW_STATE_SAVE;
	}
}

//	�ۑ�
void Goddess::Save(void)
{
	time_t timer = time(NULL);
	struct tm* local;
	local = localtime(&timer);

	char strDate[30] = {0};
	sprintf(strDate, "%4d%02d%02d_%02d%02d%02d", local->tm_year + 1900, local->tm_mon + 1, local->tm_mday, local->tm_hour, local->tm_min, local->tm_sec);

	//	�ۑ��t�@�C�����̌���
	char fileName[255] = {0};
	char textName[255] = {0};
	if(GENMODE)
	{
		sprintf(fileName, "gen\\%s_pict.bmp", strDate);
		sprintf(textName, "gen\\%s_gen.txt", strDate);
	}
	else
	{
		char tmp[255] = {0};
		sprintf(tmp, pNowDisp->strFormat, m_plot.GetSeedIndex() - 1);

		strcat(fileName, "gen\\");
		strcat(fileName, tmp);
		strcat(fileName, ".png");
		
		sprintf(textName, "gen\\%s_gen.txt", strDate);
			
	}

	//	�摜�̕ۑ�
	if(GENMODE)
	{
		SaveCaptureBmp(fileName);
	}
	else
	{
		SaveCapturePng(fileName);
	}

	//	�e�L�X�g�̕ۑ�
	m_plot.Save(textName);

	//	���̏���
	if(m_plot.Setup())
	{
		Clear(D3DCOLOR_ARGB(255, 0, 0, 0));
		m_nState = DRAW_STATE_SETUP;
	}
	else
	{
		m_nState = DRAW_STATE_FINISH;
	}

	nPlotCnt = 0;

}
