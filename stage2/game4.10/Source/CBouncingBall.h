namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// �o��class���ѷ|�@���u�����y
	// �����N�i�H��g���ۤv���{���F
	/////////////////////////////////////////////////////////////////////////////

	// tutorial_6_step3_addNewFunctionInClassCBouncingBall
	class CBouncingBall
	{
	public:
		CBouncingBall();
		void LoadBitmap();		// ���J�ϧ�
		void OnMove();			// ����
		void OnShow();			// �N�ϧζK��e��
		void SetFloor(int);		// tutorial_6_step3_�]�w�u�^������
		void SetXY(int, int);	// tutorial_6_step3_�]�w�_�l�W�ɮy��
		void SetVelocity(int);	// tutorial_6_step3_�]�w�W�ɪ��_�l�t��
	private:
		int x, y;				// �ϧήy��
		int floor;				// �a�O��Y�y��
		bool rising;			// true��W�ɡBfalse��U��
		int initial_velocity;	// ��l�t��
		int velocity;			// �ثe���t��(�I/��)
		CAnimation animation;	// �Q�ΰʵe�@�ϧ�
	};
}