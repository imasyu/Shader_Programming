#pragma once
#include <list>
#include <string>
#include "Transform.h"
#include "Direct3D.h"
#include "SphireCollider.h"

using std::string;
using std::list;

class SphireCollider;

class GameObject
{
	bool                      Dead_;
protected:
	list<GameObject*>         childList_;
	Transform	              transform_;
	GameObject*	              pParent_;
	string	                  objectName_; //オブジェクトの名前
	SphireCollider*           pCollider_;

public:
	GameObject();
	GameObject(GameObject* parent, const std::string& name);
	~GameObject();

	virtual void Initialize() =0;
	virtual void Update() =0;
	virtual void Draw() =0;
	virtual void Release() =0;
	void KillMe();
	void DrawSub();
	void UpdateSub();
	void ReleaseSub();
	void SetPosition(XMFLOAT3 position);
	void SetPosition(float x, float y, float z);
	GameObject* FindChildObject(string _objName);
	GameObject* GetRootJob();
	GameObject* FindObject(string _objName);
	void AddCollider(SphireCollider* pCollider);
	void Collision(GameObject* pTarget);
	void RoundRobin(GameObject* pTarget);
public:
	//テンプレートの定義
	template<class T>
	GameObject* Instantiate(GameObject* parent)
	{
		T* pObject;
		pObject = new T(parent);
		pObject->Initialize();
		parent->childList_.push_back(pObject);
		return pObject;
	}
};