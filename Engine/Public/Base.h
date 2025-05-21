#pragma once

/* ��� Ŭ������ �θ� �Ǵ� Ŭ���� */
/* ��� Ŭ�������� ������ ����� �������ְ����Ѵ�.  */
/* ������ ��� : ���۷��� ī��Ʈ�� �����Ѵ�. */
/* ���۷��� ī��Ʈ : ���� ����( ��ü�� �ּҸ� �����ϴ� �������� ������ ���� ) */

#include "Engine_Defines.h"

BEGIN(Engine)

class ENGINE_DLL CBase abstract
{
protected:
	CBase();
	virtual ~CBase() = default;

public:
	/* ���������� ������Ű�� ������ ����� �����ϳ�. */
	unsigned int AddRef();

	/* ���������� ���ҽ�Ű�ų� �����ϰ� �����ϱ� ������ ���� �����Ѵ�. */
	unsigned int Release();

private:
	unsigned int m_iRefCnt = {};

public:
	virtual void Free();

};
END



