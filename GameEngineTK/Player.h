/**
*	@file	Player.h
*
*	@brief	自機
*
*	@date	2015/05/08
*
*	@author	藤澤　伸治
*/
#pragma once

#include <d3d11_1.h>
#include <SimpleMath.h>
#include <Keyboard.h>
#include <vector>
#include "Obj3d.h"
#include "CollisionNode.h"

// 自機
class Player
{
public:
	// 重力加速度
	const float GRAVITY_ACC = 0.03f;
	// ジャンプ初速
	const float JUMP_SPEED_FIRST = 0.5f;
	// ジャンプ最高速
	const float JUMP_SPEED_MAX = 0.3f;
	// パーツ
	enum PARTS
	{
		PARTS_TOWER,	// 塔
		PARTS_BASE,	// 基地
		PARTS_ENGINE_R,	// 右エンジン
		PARTS_ENGINE_L,	// 左エンジン
		PARTS_FAN,	// 換気扇
		PARTS_SCORE,	// 音符

		PARTS_NUM
	};

	// コンストラクタ
	Player(DirectX::Keyboard* keyboard);
	// デストラクタ
	~Player();
	// 初期化
	void Initialize();
	// 毎フレーム更新
	void Update();
	// 行列の計算
	void Calc();
	// 描画
	void Draw();
	// 弾発射
	void FireBullet();
	// 弾リセット
	void ResetBullet();

	// 座標を取得
	const DirectX::SimpleMath::Vector3& GetTrans();
	const DirectX::SimpleMath::Vector3 & GetRot();
	// 座標を設定
	void SetTrans(const DirectX::SimpleMath::Vector3& trans);
	// 回転を設定
	void SetRot(const DirectX::SimpleMath::Vector3& rot);
	// ワールド行列を取得
	const DirectX::SimpleMath::Matrix& GetLocalWorld();
	void StartJump();
	void StartFall();
	void StopJump();
	// 当たり判定球を取得
	const SphereNode& GetCollisionNodeBullet() { return m_CollisionNodeBullet; }
	// 当たり判定球を取得
	const SphereNode& GetCollisionNodeBody() { return m_CollisionNodeBody; }

	const DirectX::SimpleMath::Vector3& GetVelocity() { return m_Velocity; }
protected:
	// メンバ変数
	// ロボットの構成パーツ
	std::vector<Obj3d>	m_Obj;
	// キーボード
	DirectX::Keyboard* m_pKeyboard;
	DirectX::Keyboard::KeyboardStateTracker m_KeyboardTracker;

	// 自機のギミックに使う角度
	float m_sinAngle;
	// 弾の速度
	DirectX::SimpleMath::Vector3 m_BulletVel;
	// 弾丸発射中フラグ
	bool m_FireFlag;

	// 当たり判定球
	SphereNode m_CollisionNodeBullet;
	// 当たり判定球
	SphereNode m_CollisionNodeBody;

	// 速度ベクトル
	DirectX::SimpleMath::Vector3 m_Velocity;
	// ジャンプ中フラグ
	bool m_isJump;
};

