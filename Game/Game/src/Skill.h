#pragma once
# include "Ability.h"
# include "TiledGameObjectTexture.h"


enum class DisplayLayer;
class EffectAnime;

// �X�L�����ł̃L�����ړ���A�j���ɉ��������������蔻�蓙�̎����̂��߁A�X�L�����ɃN���X���쐬����B

// �X�L���̊��N���X
class Skill
{
public:
	enum class State {
		Complete,
		Continue,
	};

	struct EffectData {
		const String textureStr;		// �e�N�X�`�� 
		const DisplayLayer layer;		// �\�����C���[
		const Size tileSize;			// 1�R�}�̃T�C�Y
		const double endTime;			// �G�t�F�N�g�I���܂ł̎��ԁi�^�C���A�j���Ɠ������ԂƂ��邱�Ɓj
		const int32 maxCount;			// �S�R�}��
		const int32 xNum;				// ���̃R�}��
		const int32 yNum;				// �c�̃R�}��
		const Size displayRegion;		// �G�t�F�N�g�̕\���̈�	
	};

	struct Data {
		const String name;		// �Z��
		enum class Genre {
			Physical,					// �����Z
			AssistMyself,				// �����ւ̕⏕�Z
			AssistSomeone,				// ���ւ̕⏕�Z
			SingleEffect,				// ���ւ̒P�̖��@�Z
			AreaOfEffect,				// ���𒆐S�Ƃ������@�Z
			AreaOfEffectFocusingMyself	// ���𒆐S�Ƃ������@�Z
		}const genre;			// �Z�̕���
		//const Type type;		// �U�������F �a�A�ŁA�ˁA�΁A���A�c�A��	
		const int32 power;		// �З� ("+"�_���[�W / "-"��)
		const int32 state;		// ��Ԉُ�F 0x00000000 �` 0x11111111
		const Size region;		// �Z�̓����蔻��̈�
		const int32  attackNum;	// �U����
		Data(const String& n, const Genre& g, const int32& p, const int32& s, const Size& r, const int32& a);
	}_data;

	Skill();

	Skill(const EffectData& eData, const Data& sData);	//���̃R���X�g���N�^�ɓn�������ɂ��G�t�F�N�g������


	virtual State execute(
		RectF& actor,
		Direction& direction,
		const Ability ability,
		const Group& targetGroup,
		TiledGameObjectTexture& tiledTexture,
		std::function<void(const int32)> func)
	{
		return State::Complete;
	}
	virtual State execute(
		Circle& actor,
		Direction& direction,
		const Ability ability,
		const Group& targetGroup,
		TiledGameObjectTexture& tiledTexture,
		std::function<void(const int32)> func)
	{
		return State::Complete;
	}

protected:
	std::shared_ptr<EffectAnime> _effect;
	bool _isActiveTileAnime;		// �^�C���A�j�����s����
	bool _isActiveEffect;			// �G�t�F�N�g�A�j�����s����
	int32 _attackNumAccum;			// �U��������s������
};

/* --------------------------------------------------------------------------------------*/
/*		�\�[�h�X�L��																	 */
/* --------------------------------------------------------------------------------------*/
class Slash : public Skill
{
public:
	Slash();

	//State execute(RectF& actor, Direction& direction, const Ability ability);
	State execute(
		RectF& actor,
		Direction& direction,
		const Ability ability,
		const Group& targetGroup,
		TiledGameObjectTexture& tiledTexture,
		std::function<void(const int32)> func);
private:

};

class SonicBlade : public Skill
{
public:
	SonicBlade();

	//State execute(RectF& actor, Direction& direction, const Ability ability);
	State execute(RectF& actor,
		Direction& direction,
		const Ability ability,
		const Group& targetGroup,
		TiledGameObjectTexture& tiledTexture,
		std::function<void(const int32)> func);
private:

};