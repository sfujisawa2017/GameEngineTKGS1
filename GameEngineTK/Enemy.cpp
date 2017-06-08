//--------------------------------------------------------------------------------------
// �t�@�C����: Enemy.cpp
// �쐬��:
// �쐬��:
// ����:
//--------------------------------------------------------------------------------------

#include "Enemy.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

Enemy::Enemy(DirectX::Keyboard* keyboard)
{
	m_pKeyboard = keyboard;

	m_sinAngle = 0.0f;

	Initialize();
}

Enemy::~Enemy()
{
}

//-----------------------------------------------------------------------------
// ������
//-----------------------------------------------------------------------------
void Enemy::Initialize()
{
	// ���@�p�[�c�̃��[�h
	m_Obj.resize(PARTS_NUM);
	m_Obj[PARTS_TOWER].LoadModel(L"Resources/tower.cmo");
	m_Obj[PARTS_BASE].LoadModel(L"Resources/base.cmo");
	m_Obj[PARTS_ENGINE_R].LoadModel(L"Resources/engine.cmo");
	m_Obj[PARTS_ENGINE_L].LoadModel(L"Resources/engine.cmo");
	m_Obj[PARTS_FAN].LoadModel(L"Resources/fan.cmo");
	m_Obj[PARTS_SCORE].LoadModel(L"Resources/score.cmo");
	// �e�q�֌W�̍\�z�i�q���ɐe���Z�b�g�j
	m_Obj[PARTS_BASE].SetObjParent(
		&m_Obj[PARTS_TOWER]);

	m_Obj[PARTS_SCORE].SetObjParent(
		&m_Obj[PARTS_BASE]);

	m_Obj[PARTS_ENGINE_R].SetObjParent(
		&m_Obj[PARTS_TOWER]);
	m_Obj[PARTS_ENGINE_L].SetObjParent(
		&m_Obj[PARTS_TOWER]);

	m_Obj[PARTS_FAN].SetObjParent(
		&m_Obj[PARTS_TOWER]);

	// �e����̃I�t�Z�b�g�i���[�J���̍��W����j
	m_Obj[PARTS_TOWER].SetScale(
		Vector3(2, 2, 2));

	m_Obj[PARTS_BASE].SetTranslation(
		Vector3(0, 0.7f, 0));

	m_Obj[PARTS_SCORE].SetTranslation(
		Vector3(0, 1.0f, 0));
	m_Obj[PARTS_SCORE].SetScale(
		Vector3(2, 2, 2));

	m_Obj[PARTS_ENGINE_R].SetTranslation(
		Vector3(0.22f, 0.3f, 0.22f));
	m_Obj[PARTS_ENGINE_R].SetRotation(
		Vector3(0, XMConvertToRadians(45), 0));

	m_Obj[PARTS_ENGINE_L].SetTranslation(
		Vector3(-0.22f, 0.3f, 0.22f));
	m_Obj[PARTS_ENGINE_L].SetRotation(
		Vector3(0, XMConvertToRadians(-45), 0));

	m_Obj[PARTS_FAN].SetTranslation(
		Vector3(0, 0.3f, 1.0f));

	// �������W�������_���Ɍ���
	Vector3 pos;

	pos.x = rand() % 10;
	pos.z = rand() % 10;

	SetTrans(pos);

	m_Timer = 0;
	m_DistAngle = 0;

}

//-----------------------------------------------------------------------------
// �X�V
//-----------------------------------------------------------------------------
void Enemy::Update()
{
	Keyboard::State keystate = m_pKeyboard->GetState();
	m_KeyboardTracker.Update(keystate);

	// ���@�p�[�c�̃M�~�b�N
	{
		// ���@�̊p�x��ϓ�
		Vector3 angle;

		angle = m_Obj[PARTS_SCORE].GetRotation();
		m_Obj[PARTS_SCORE].SetRotation(
			angle + Vector3(0.2f, 0.1f, 0));

		// �T�C���̈����̊p�x�����񂾂񑝂���
		m_sinAngle += 0.1f;
		// �t�@���̊p�x���������肫���肷��(-1�`+1)
		float fan_angle = sinf(m_sinAngle) * 3.0f;
		/*m_Obj[PLAYER_PARTS_FAN].SetRotation(
		Vector3(0, 0, fan_angle));*/
		//m_Obj[PARTS_FAN].SetTranslation(
		//	Vector3(sinf(m_sinAngle), 0, cosf(m_sinAngle)*3.0f));
	}

	m_Timer--;
	if (m_Timer < 0)
	{
		// �ڕW�p�x�̍Ē��I
		m_Timer = 60;
		// -0.5�`+0.5�̗���
		float rnd = (float)rand() / RAND_MAX - 0.5f;
		// -90�`+90�̗���
		rnd *= 180.0f;

		rnd = XMConvertToRadians(rnd);

		m_DistAngle += rnd;
	}

	{
		// ���@�̊p�x��ϓ�
		Vector3 rot = GetRot();

		float angle = m_DistAngle - rot.y;

		if (angle > XM_PI)
		{
			angle -= XM_2PI;
		}
		if (angle < -XM_PI)
		{
			angle += XM_2PI;
		}

		rot.y += angle *0.05f;

		SetRot(rot);
	}
	
	// �@�̂̌����Ă�������ɑO�i
	{
		// �ړ��x�N�g��
		Vector3 moveV(0, 0, -0.1f);
		// ���̊p�x�ɍ��킹�Ĉړ��x�N�g������]
		// ��]�s��
		float angle = m_Obj[0].GetRotation().y;
		Matrix rotmat = Matrix::CreateRotationY(angle);
		moveV = Vector3::TransformNormal(moveV, rotmat);
		// ���@�̍��W���ړ�
		Vector3 pos = m_Obj[0].GetTranslation();
		pos += moveV;
		m_Obj[0].SetTranslation(pos);
	}

	// �s��X�V
	Calc();
}

//-----------------------------------------------------------------------------
// �s��X�V
//-----------------------------------------------------------------------------
void Enemy::Calc()
{
	for (std::vector<Obj3d>::iterator it = m_Obj.begin();
		it != m_Obj.end();
		it++)
	{
		it->Update();
	}
}

//-----------------------------------------------------------------------------
// �`��
//-----------------------------------------------------------------------------
void Enemy::Draw()
{
	for (std::vector<Obj3d>::iterator it = m_Obj.begin();
		it != m_Obj.end();
		it++)
	{
		it->Draw();
	}
}

const DirectX::SimpleMath::Vector3& Enemy::GetTrans()
{
	// �^���N�p�[�c�̍��W��Ԃ�
	return m_Obj[0].GetTranslation();
}

const DirectX::SimpleMath::Vector3& Enemy::GetRot()
{
	// �^���N�p�[�c�̍��W��Ԃ�
	return m_Obj[0].GetRotation();
}

void Enemy::SetTrans(const DirectX::SimpleMath::Vector3& trans)
{
	// �^���N�p�[�c�̍��W��ݒ�
	m_Obj[0].SetTranslation(trans);
}

void Enemy::SetRot(const DirectX::SimpleMath::Vector3& rot)
{
	// �^���N�p�[�c�̍��W��ݒ�
	m_Obj[0].SetRotation(rot);
}

const DirectX::SimpleMath::Matrix& Enemy::GetLocalWorld()
{
	// �^���N�p�[�c�̃��[���h�s���Ԃ�
	return m_Obj[0].GetWorld();
}