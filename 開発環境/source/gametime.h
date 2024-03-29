//==========================================
//
//  �Q�[�������Ԍv���̃N���X(gametime.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _GAMETIME_H_
#define _GAMETIME_H_

//==========================================
//  �N���X��`
//==========================================
class CGameTime
{
public:

	//�����o�֐�
	CGameTime();
	~CGameTime();

	void Init(void);
	void Uninit(void);
	void Update(void);

	int GetDeltaTimeInt(void) { return m_nDeltaTime * m_fScale; }
	float GetDeltaTimeFloat(void) { return m_fDelta * m_fScale; }
	void AddScaling(float scale, float keep);
	void AddScale(float scale);
	void AddTime(float keep);
	void SetScaling(float scale, float keep);
	void SetScale(float scale);
	void SetTime(float keep);
	float GetScale() { return m_fScale; }
	float GetTime() { return m_fScaleTime; }

private:

	// �����o�֐�
	void Scaling();

	//�����o�ϐ�
	int m_nCurrentTime; //���ݎ���
	int m_nOldTime; //�O�񎞊�
	int m_nDeltaTime; //���ݎ��� - �O�񎞊�
	float m_fDelta; //1�b�Ԃɂ�����o�ߎ��Ԃ̊���
	float m_fScale; // �o�ߎ��Ԕ{��
	float m_fScaleTime; // �{���K�p����

};

#endif
