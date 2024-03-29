//==========================================
//
//  �Q�[���V�[���̃J����(camera_game.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _CAMERA_GAME_H_
#define _CAMERA_GAME_H_
#include "camera.h"

//==========================================
//  �N���X��`
//==========================================
class CCameraGame : public CCamera
{
public:

	//�����o�֐�
	CCameraGame();
	~CCameraGame();

	HRESULT Init(void) override;
	void Update(void) override;

	void SetQuake(const D3DXVECTOR3& range, float time) override;
	void AddQuake(const D3DXVECTOR3& range, float time = 0.0f) override;

private:

	//�����o�֐�
	void MovePlayer(void);
	void LockBoss(void);
	void LockRush();
	void Quake();

	// ��ʗh��p�̍\����
	struct QuakeData
	{
		D3DXVECTOR3 rangeR; // �����_�̗h��
		D3DXVECTOR3 rangeV; // ���_�̗h��
		float time; // �p������
	};

	// �����o�ϐ�
	QuakeData m_Quake; // �h����

};

#endif
