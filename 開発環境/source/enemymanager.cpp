//==========================================
//
//  �G�l�~�[�}�l�[�W��(enemymanager.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "enemymanager.h"
#include "enemy.h"
#include "manager.h"
#include "input.h"
#include "gamemanager.h"
#include "boss.h"

//==========================================
//  �N���X��`
//==========================================
namespace
{
	const D3DXVECTOR3 BOSS_POS = D3DXVECTOR3(1800.0f, 150.0f, 0.0f); // �{�X�̃|�W�V����
	const char* ENEMY_FILE = "data\\TXT\\Enemy.txt"; // �G�̔z�u��񂪕ۑ����ꂽ�t�@�C��
}

//==========================================
//  �R���X�g���N�^
//==========================================
CEnemyManager::CEnemyManager() :
	m_pInfo(nullptr),
	m_pBoss(nullptr),
	m_bPopFrag(false),
	m_bBossCrush(false),
	m_bRush(false)
{

}

//==========================================
//  �f�X�g���N�^
//==========================================
CEnemyManager::~CEnemyManager()
{

}

//==========================================
//  ����������
//==========================================
void CEnemyManager::Init()
{
	// ���̓ǂݍ���
	Load();
}

//==========================================
//  �I������
//==========================================
void CEnemyManager::Uninit()
{
	// �ݒu���̔j��
	if (m_pInfo != nullptr)
	{
		delete m_pInfo;
		m_pInfo = nullptr;
	}

	// ���g�̍폜
	delete this;
}

//==========================================
//  �X�V����
//==========================================
void CEnemyManager::Update()
{
	// �{�X�̏o��
	if (!m_bBossCrush)
	{
		if (CGameManager::GetState() == CGameManager::STATE_BOSS)
		{
			if (!m_bPopFrag) // �{�X�o���t���O
			{
				m_pBoss = CEnemy::Create(BOSS_POS, CEnemy::BOSS);
				m_bPopFrag = true;
			}
			else
			{
				if (m_pBoss->GetState() == CBoss::RUSH) // ���b�V�����
				{
					m_bRush = true;
				}
			}
		}
	}
}

//==========================================
//  �ǂݍ��ݏ���
//==========================================
void CEnemyManager::Load()
{
	//���[�J���ϐ��錾
	FILE* pFile; // �t�@�C���|�C���^
	char aStr[256]; // �s�v�ȕ�����̋L�^�p

	//�t�@�C����ǂݎ���p�ŊJ��
	pFile = fopen(ENEMY_FILE, "r");

	if (pFile != NULL)
	{
		while (1)
		{
			// �e�L�X�g�ǂݍ���
			fscanf(pFile, "%s", &aStr[0]);

			// ��������
			if (strcmp(&aStr[0], "ENEMY_SET") == 0) // �G���̐ݒ�
			{
				// �G�z�u�p�ϐ�
				D3DXVECTOR3 pos;
				CEnemy::TYPE type = CEnemy::NONE;

				while (1)
				{
					// �e�L�X�g�ǂݍ���
					fscanf(pFile, "%s", &aStr[0]);

					// �������򏈗�
					if (strcmp(&aStr[0], "POS") == 0) // ���W
					{
						fscanf(pFile, "%f", &pos.x);
						fscanf(pFile, "%f", &pos.y);
						fscanf(pFile, "%f", &pos.z);
					}
					else if (strcmp(&aStr[0], "TYPE") == 0) // ���
					{
						fscanf(pFile, "%d", &type);
					}
					else if (strcmp(&aStr[0], "ENEMY_END") == 0) // �z�u���̏I���
					{
						// �z�u
						CEnemy::Create(pos, type);

						// ���[�v�𔲂���
						break;
					}
				}
			}
			else if (strcmp(&aStr[0], "END_FILE") == 0) // �t�@�C���̏I�[
			{
				// �t�@�C�������
				fclose(pFile);

				// ���[�v�𔲂���
				break;
			}
		}
	}
}

//==========================================
//  ��������
//==========================================
CEnemyManager* CEnemyManager::Create()
{
	// �C���X�^���X����
	CEnemyManager* manager = new CEnemyManager;

	// NULL�`�F�b�N
	if (manager == nullptr) { return nullptr; }

	// ����������
	manager->Init();

	// �l��Ԃ�
	return manager;
}
