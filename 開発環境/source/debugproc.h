//==========================================================
//
//�f�o�b�O�\������ [debugproc.h]
//Author Ibuki Okusada
// Added by Tomoya Kanazaki
//
//==========================================================
#ifndef _DEBUGPROC_H_		//���̃}�N������`����Ă��Ȃ��ꍇ
#define _DEBUGPROC_H_


//**********************************************************
//�l�[���X�y�[�X�̒�`
//**********************************************************
namespace DebugProc
{
	void Init(void); // ����������
	void Uninit(void); // �I������
	void Update(void); // �X�V����
	void Draw(void); // �`�揈��
	void Print(const char *fmt, ...); // ���������
};

#endif