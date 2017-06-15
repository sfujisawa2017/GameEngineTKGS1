/// <summary>
/// �Փ˔��胉�C�u����
/// </summary>
#pragma once

//#include <Windows.h>
#include <d3d11_1.h>
#include <SimpleMath.h>

// ��
class Sphere
{
public:
	// ���S���W
	DirectX::SimpleMath::Vector3 Center;
	// ���a
	float Radius;
	// �R���X�g���N�^
	Sphere()
	{
		// �f�t�H���g���a��1���[�g��
		Radius = 1.0f;
	}
};

// ����
class Segment
{
public:
	// �n�_���W
	DirectX::SimpleMath::Vector3 Start;
	// �I�_���W
	DirectX::SimpleMath::Vector3 End;
};

bool CheckSphere2Sphere(const Sphere & sphereA, const Sphere & sphereB);