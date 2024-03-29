//==========================================
//
//  ���[�V�����N���X(moton.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "motion.h"
#include "model.h"

//==========================================
//  �}�N����`
//==========================================
#define TXTFILENAME_MOTION "data\\TXT\\MotionData.txt" //���[�V���������������e�L�X�g�t�@�C���̃p�X

//==========================================
//  �ÓI�����o�ϐ��錾
//==========================================
CMotion::INFO CMotion::m_aInfo[MAX_NUM] = {};
int CMotion::m_nNumMotion = 0;

//==========================================
//  �R���X�g���N�^
//==========================================
CMotion::CMotion()
{
	m_ppModel = NULL;
	memset(&m_Info, 0, sizeof(m_Info));
	for (int nCnt = 0; nCnt < MAX_NUM; nCnt++)
	{
		m_startKey[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_startKey[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
	m_nNumModel = 0;
	m_nCntFrame = 0;
	m_nCntKey = 0;
	m_bMotion = false;
}

//==========================================
//  �f�X�g���N�^
//==========================================
CMotion::~CMotion()
{

}

//==========================================
//  �X�V����
//==========================================
void CMotion::Update(void)
{
	//NULL�`�F�b�N
	if (m_ppModel != NULL)
	{
		//���[�V�������������Ă����甲����
		if (m_bMotion)
		{
			return;
		}

		//�L�[�̗L�����m�F
		if (m_Info.nNumKey > 0)
		{
			int nNowKey = m_nCntKey; // ���݂̃L�[
			int nNextkey = (nNowKey + 1) % m_Info.nNumKey; //���̃L�[
			int nFrame = 0;
			if (nNowKey != -1)
			{
				nFrame = m_Info.aKeyInfo[nNowKey].nFrame;
			}

			//���f�������̃��[�V������ݒ�
			for (int nCntModel = 0; nCntModel < m_nNumModel; nCntModel++)
			{
				//�O��̒l���擾
				m_oldKey.pos = m_ppModel[nCntModel]->GetPos();
				m_oldKey.rot = m_ppModel[nCntModel]->GetRot();

				//�������Z�o
				D3DXVECTOR3 posDeff, rotDeff;
				if (m_nCntKey == -1)
				{
					posDeff = (m_Info.aKeyInfo[nNextkey].aKey[nCntModel].pos - m_startKey[nCntModel].pos);
					rotDeff = (m_Info.aKeyInfo[nNextkey].aKey[nCntModel].rot - m_startKey[nCntModel].rot);
				}
				else
				{
					posDeff = (m_Info.aKeyInfo[nNextkey].aKey[nCntModel].pos - m_Info.aKeyInfo[nNowKey].aKey[nCntModel].pos) / (float)nFrame;
					rotDeff = (m_Info.aKeyInfo[nNextkey].aKey[nCntModel].rot - m_Info.aKeyInfo[nNowKey].aKey[nCntModel].rot) / (float)nFrame;
				}

				//�p�x�̕␳
				if (rotDeff.x < -D3DX_PI) //x
				{
					rotDeff.x += D3DX_PI * 2;
				}
				else if (rotDeff.x > D3DX_PI)
				{
					rotDeff.x += -D3DX_PI * 2;
				}

				if (rotDeff.y < -D3DX_PI) //y
				{
					rotDeff.y += D3DX_PI * 2;
				}
				else if (rotDeff.y > D3DX_PI)
				{
					rotDeff.y += -D3DX_PI * 2;
				}

				if (rotDeff.z < -D3DX_PI) //z
				{
					rotDeff.z += D3DX_PI * 2;
				}
				else if (rotDeff.z > D3DX_PI)
				{
					rotDeff.z += -D3DX_PI * 2;
				}

				//���݂̒l���Z�o
				D3DXVECTOR3 posDest, rotDest;
				if (m_nCntKey == -1)
				{
					posDest = m_oldKey.pos + posDeff;
					rotDest = m_oldKey.rot + rotDeff;
				}
				else
				{
					posDest = m_oldKey.pos + posDeff;
					rotDest = m_oldKey.rot + rotDeff;
				}

				//�Z�o�����l�̓K�p
				if (nCntModel == 0)
				{
					m_ppModel[nCntModel]->SetPos(posDest);
					m_ppModel[nCntModel]->SetRot(rotDest);
				}
				else
				{
					m_ppModel[nCntModel]->SetRot(rotDest);
				}
			}

			if (m_nCntKey == -1)
			{
				//�L�[�̍X�V
				m_nCntKey = nNextkey;
				m_nCntFrame = 0;
			}
			else
			{
				//�t���[���J�E���g�����Z
				m_nCntFrame++;

				//�L�[�̍X�V���`�F�b�N
				if (m_Info.aKeyInfo[nNowKey].nFrame != 0)
				{
					if (m_nCntFrame == nFrame)
					{
						//�L�[�̍X�V
						if (m_Info.bLoop)
						{
							m_nCntKey = nNextkey;
							m_nCntFrame = 0;
						}
						else
						{
							m_bMotion = true;
						}
					}
				}
			}
		}
	}
}

//==========================================
//  ���f���̐ݒ菈��
//==========================================
void CMotion::SetModel(CModel **ppModel, int nNum, MOTION type)
{
	//���f�����L�^
	m_ppModel = ppModel;

	//���f�������L�^
	m_nNumModel = nNum;

	//�g�p���郂�[�V������ݒ�
	m_Info = m_aInfo[type];

	//���[�V�����J�n���̒l���擾
	for (int nCnt = 0; nCnt < m_Info.nNumModel; nCnt++)
	{
		m_startKey[nCnt].pos = m_ppModel[nCnt]->GetPos();
		m_startKey[nCnt].rot = m_ppModel[nCnt]->GetRot();
	}
}

//==========================================
//  ���[�V�����̐ݒ菈��
//==========================================
void CMotion::Set(MOTION type)
{
	//�g�p���郂�[�V������ݒ�
	m_Info = m_aInfo[type];

	//���[�V�����J�n���̒l���擾
	for (int nCnt = 0; nCnt < m_Info.nNumModel; nCnt++)
	{
		m_startKey[nCnt].pos = m_ppModel[nCnt]->GetPos();
		m_startKey[nCnt].rot = m_ppModel[nCnt]->GetRot();
	}

	//�J�E���^�[�����Z�b�g
	m_nCntKey = -1;
	m_nCntFrame = 0;
	m_bMotion = false;
}

//==========================================
//  �ǂݍ��ݏ���
//==========================================
void CMotion::Load(void)
{
	//���[�J���ϐ��錾
	FILE *pFile; //�t�@�C����
	char aStr[256]; //�s�v�ȕ�����̋L�^�p
	int nCntInfo = 0; //���݂̃��[�V�����ԍ�
	int nCntKey = 0; //���݂̃L�[�ԍ�
	int nCntModel = 0; //���݂̃��f���ԍ�

	//�t�@�C����ǂݎ���p�ŊJ��
	pFile = fopen(TXTFILENAME_MOTION, "r");

	if (pFile != NULL)
	{
		while (1)
		{
			//��������擾
			fscanf(pFile, "%s", &aStr[0]);

			if (strcmp(&aStr[0], "NUM_MOTION") == 0)
			{
				fscanf(pFile, "%s", &aStr[0]); //=
				fscanf(pFile, "%d", &m_nNumMotion); //���[�V�������擾
			}
			else if (strcmp(&aStr[0], "LOOP") == 0)
			{
				//���[�v�̗L�����擾
				fscanf(pFile, "%s", &aStr[0]); //=
				fscanf(pFile, "%d", &m_aInfo[nCntInfo].bLoop);
			}
			else if (strcmp(&aStr[0], "NUM_KEY") == 0)
			{
				//�L�[���̎擾
				fscanf(pFile, "%s", &aStr[0]); //=
				fscanf(pFile, "%d", &m_aInfo[nCntInfo].nNumKey);
			}
			else if (strcmp(&aStr[0], "NUM_MODEL") == 0)
			{
				//���f�����̎擾
				fscanf(pFile, "%s", &aStr[0]); //=
				fscanf(pFile, "%d", &m_aInfo[nCntInfo].nNumModel);
			}
			else if (strcmp(&aStr[0], "FRAME") == 0)
			{
				//�t���[�������擾
				fscanf(pFile, "%s", &aStr[0]); //=
				fscanf(pFile, "%d", &m_aInfo[nCntInfo].aKeyInfo[nCntKey].nFrame);
			}
			else if (strcmp(&aStr[0], "POS") == 0)
			{
				//���W���擾
				fscanf(pFile, "%s", &aStr[0]); //=
				D3DXVECTOR3 pos;
				fscanf(pFile, "%f", &pos.x);
				fscanf(pFile, "%f", &pos.y);
				fscanf(pFile, "%f", &pos.z);

				m_aInfo[nCntInfo].aKeyInfo[nCntKey].aKey[nCntModel].pos = pos;
			}
			else if (strcmp(&aStr[0], "ROT") == 0)
			{
				//�p�x���擾
				fscanf(pFile, "%s", &aStr[0]); //=
				D3DXVECTOR3 rot;
				fscanf(pFile, "%f", &rot.x);
				fscanf(pFile, "%f", &rot.y);
				fscanf(pFile, "%f", &rot.z);

				m_aInfo[nCntInfo].aKeyInfo[nCntKey].aKey[nCntModel].rot = rot;
			}
			else if (strcmp(&aStr[0], "END_MOTIONSET") == 0)
			{
				//���[�V�����ԍ���i�߂�
				nCntInfo++;

				//�L�[�ԍ��ƃ��f���ԍ������Z�b�g����
				nCntModel = 0;
				nCntKey = 0;
			}
			else if (strcmp(&aStr[0], "END_KEYSET") == 0)
			{
				//�L�[�ԍ���i�߂�
				nCntKey++;

				//���f���ԍ������Z�b�g����
				nCntModel = 0;
			}
			else if (strcmp(&aStr[0], "END_KEY") == 0)
			{
				//���f���ԍ���i�߂�
				nCntModel++;
			}
			if (strcmp(&aStr[0], "END_SCRIPT") == 0)
			{
				//�I�[
				break;
			}
		}
		fclose(pFile);
	}
}
