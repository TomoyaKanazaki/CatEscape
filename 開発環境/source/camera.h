//==========================================
//
//  �J�����N���X(camera.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

//==========================================
//  �J�����N���X�̒�`
//==========================================
class CCamera
{
public:
	CCamera(); //�R���X�g���N�^
	~CCamera(); //�f�X�g���N�^

	//�����o�֐�
	virtual HRESULT Init(void);
	void Uninit(void);
	virtual void Update(void);
	void SetCamera(void);
	D3DXVECTOR3 GetPosR(void) { return m_posR; }
	D3DXVECTOR3 GetPosV(void) { return m_posV; }
	void SetPosR(D3DXVECTOR3 pos) { m_posR = pos; }
	void SetPosV(D3DXVECTOR3 pos) { m_posV = pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	D3DXMATRIX GetMtxPro(void) { return m_mtxProjection; }
	D3DXMATRIX CreateViewMatrix(void);
	void SwitchDebug(void) { m_bDebug = !m_bDebug; }
	bool GetDebug(void) { return m_bDebug; }
	bool OnScreen(const D3DXVECTOR3 pos) const; // �X�N���[�����̔���
	D3DXVECTOR3 WorldToScreen(const D3DXVECTOR3& posWorld) const;
	//D3DXVECTOR3 ScreenToWorld(const D3DXVECTOR3& posScreen) const;
	virtual void SetQuake(const D3DXVECTOR3& range, float time) {};
	virtual void AddQuake(const D3DXVECTOR3& range, float time) {};

protected:
#define CAMERA_DISTANCE (-500.0f) //���_����v���C���[�̋���
#define R_HEIGHT (10.0f) //���_�̍���
#define V_HEIGHT (130.0f) //�����_�̍���
#define MAX_ROT (D3DX_PI * 0.99f) //���_�̌��E�p
#define MIN_ROT (D3DX_PI * 0.01f) //���_�̌��E�p
#define DEFAULT_FAV (45.0f) //����p�̋K��l
#define MAX_FAV (54.0f) //����p�̋K��l

	//�����o�֐�
	void FirstPerson(void);
	void ThirdPerson(void);
	void Move(void);

	//�����o�ϐ�
	D3DXVECTOR3 m_posV; //���_
	D3DXVECTOR3 m_posR; //�����_
	D3DXVECTOR3 m_vecU; //������x�N�g��
	D3DXMATRIX m_mtxProjection; //�v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX m_mtxView; //�r���[�}�g���b�N�X
	D3DXVECTOR3 m_rot; //X�̌v�Z�Ɏg�p����p�x
	D3DXVECTOR3 m_diff; //�v���C���[���W�Ƃ̍���
	float m_fFov; //����p
	bool m_bDebug; //�f�o�b�O�t���O

};

#endif
