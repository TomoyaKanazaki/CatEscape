//==========================================
//
//  ������@(tutorial.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_
#include "object2D.h"

//==========================================
//  �N���X��`
//==========================================
class CTutorial : public CObject2D
{
public:

	//�����o�֐�
	CTutorial(int nPriority = 7);
	~CTutorial();

	//�����o�֐�
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//�ÓI�����o�֐�
	static CTutorial* Create();

private:

	// �ÓI�����o�ϐ�
	static int m_nIdx;
};

#endif
