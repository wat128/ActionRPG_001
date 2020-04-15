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
			AssistMyself,				// �⏕�Z�i���j
			AssistSomeone,				// �⏕�Z�i���j
			SingleEffect,				// �P�̖��@�i���j
			AreaOfEffect,				// �͈͖��@�i�����S�j
			AreaOfEffectFocusingMyself	// �͈͖��@�Z�i�����S�j
		}const genre;			// �Z�̕���

		enum class Type {
			Void,						// ��
			Slash,						// �a		
			Strike,						// ��
			Spear,						// ��
			Fire,						// ��
			Water,						// ��
			Thunder,					// ��
			Wind,						// ��
			Earth,						// �y
			Shine,						// ��
			Dark,						// ��
		}const type;			// �Z�^�C�v	

		int32 power;			// �З� ("+"�_���[�W / "-"��)
		struct Buff {
			double attack;
			double defense;
			double agility;
			double intel;
			double resist;
			double time;				// �b�P��
		}const buff;			// �o�t�f�o�t�i"1"��� �F"1.1"�o�t / "0.9"�f�o�t�j

		const int32 state;		// ��Ԉُ�F 0x00000000 �` 0x11111111
		const Size region;		// �Z�̓����蔻��̈�
		const int32  attackNum;	// �U����

		Data(const String& n, const Genre& g, const Type& t, const int32& p, const Buff& b, const int32& s, const Size& r, const int32& a);
	}_data;

	Skill();

	Skill(const EffectData& eData, const Data& sData);	//���̃R���X�g���N�^�ɓn�������ɂ��G�t�F�N�g������
	
	virtual State execute(
		RectF& actor,
		Direction& direction,
		const Ability& ability,
		const Group& targetGroup,
		TiledGameObjectTexture& tiledTexture,
		std::function<void(const int32)> func)
	{
		return State::Complete;
	}

	virtual State execute(
		Circle& actor,
		Direction& direction,
		const Ability& ability,
		const Group& targetGroup,
		TiledGameObjectTexture& tiledTexture,
		std::function<void(const int32)> func)
	{
		return State::Complete;
	}

	virtual State execute(
		const Ability& ability,
		const Group& targetGroup,
		const int32& target,
		TiledGameObjectTexture& tiledTexture)
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
		const Ability& ability,
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
		const Ability& ability,
		const Group& targetGroup,
		TiledGameObjectTexture& tiledTexture,
		std::function<void(const int32)> func);
private:

};

/* --------------------------------------------------------------------------------------*/
/*		�o�t�E�񕜃X�L���i�g�p�҂̂݁j													 */
/* --------------------------------------------------------------------------------------*/

class BuildUp : public Skill
{
public:
	BuildUp();

	State execute(
		const Ability& ability,
		const Group& targetGroup,
		const int32 &target,
		TiledGameObjectTexture& tiledTexture);
private:

};