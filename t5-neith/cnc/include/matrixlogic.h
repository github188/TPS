/** @defgroup ��������߼���Ԫ
 *  @version 
 *  @author   wk
 *  @date     2017.5.19
 */

#pragma once

#define NUM_MATRIX_WIDTH    160
#define NUM_MATRIX_HEIGHT   110

class CMatrixLogic : public CNotifyUIImpl, public Singleton<CMatrixLogic> 
{
public:
	CMatrixLogic();
	~CMatrixLogic();

    //���µ�ǰ����״̬
	void UpdateMatrixTip(const TTPCurMatrixInfo& tTPCurMatrixInfo);//���¾����ͷ���������ͨ����
    void UpdateMatrixInfo(const TTPCurMatrixInfo& tTPCurMatrixInfo);//���¾������ݣ���Ӧ��ѡ״̬��
protected:

    /** ��ʼ����Ϣ 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnInit(TNotifyUI& msg);
	
	/*--------�������--------*/
	/** �򿪱༭Ԥ��
	 *  @param[in] 
	 *  @node 
	 *  @return 
	 */
	bool OnBtnEditPreplan(TNotifyUI& msg);
	/** ����Ԥ��
	 *  @param[in] 
	 *  @node 
	 *  @return 
	 */
	bool OnBtnSavePreplan(TNotifyUI& msg);
	/** Ӧ��Ԥ��
	 *  @param[in] 
	 *  @node 
	 *  @return 
	 */
	bool OnBtnApplyPreplan(TNotifyUI& msg);
    // �л������Ӧ����
	bool OnOptIsUseFulSelChange(TNotifyUI& msg);


	/*--------�༭����--------*/
	/** ����༭Ԥ��
	 *  @param[in] 
	 *  @node 
	 *  @return 
	 */
	bool OnBtnUIReName(TNotifyUI& msg);
	/** Ӧ�ñ༭Ԥ��
	 *  @param[in] 
	 *  @node 
	 *  @return 
	 */
	bool OnBtnUIApply(TNotifyUI& msg);
	/** ɾ���༭Ԥ��
	 *  @param[in] 
	 *  @node 
	 *  @return 
	 */
	bool OnBtnUIDelete(TNotifyUI& msg);
	/** ȡ���༭Ԥ��
	 *  @param[in] 
	 *  @node 
	 *  @return 
	 */
	bool OnBtnUICancel(TNotifyUI& msg);

	/*--------�������--------*/
	/** ȡ��
	 *  @param[in] 
	 *  @node 
	 *  @return 
	 */
	bool OnBtnSaveUICancel(TNotifyUI& msg);
	/** ����
	 *  @param[in] 
	 *  @node 
	 *  @return 
	 */
	bool OnBtnSaveUISave(TNotifyUI& msg);

    /*--------����������--------*/
	/** ȡ��
	 *  @param[in] 
	 *  @node 
	 *  @return 
	 */
	bool OnBtnReNameUICancel(TNotifyUI& msg);
	/** ����
	 *  @param[in] 
	 *  @node 
	 *  @return 
	 */
	bool OnBtnReNameUISave(TNotifyUI& msg);

    //�᳡��Ϣ֪ͨ
    bool OnCnsInfoNotify(WPARAM wParam, LPARAM lParam, bool& bHandle);
    //�������ø���
    bool OnMatrixConFigNotify(WPARAM wParam, LPARAM lParam, bool& bHandle);
    //����Ԥ����Ϣ֪ͨ
    bool OnMatrixSceneInfoNotify(WPARAM wParam, LPARAM lParam, bool& bHandle);
    //��ǰ����������Ϣ֪ͨ
    bool OnCurMatrixInfoNotify(WPARAM wParam, LPARAM lParam, bool& bHandle);
    //�������Ԥ������
    bool OnSaveMatrixSceneInd(WPARAM wParam, LPARAM lParam, bool& bHandle);
    //����������Ԥ������
    bool OnReNameMatrixSceneInd(WPARAM wParam, LPARAM lParam, bool& bHandle);
    //ɾ������Ԥ������
    bool OnDeleteMatrixSceneInd(WPARAM wParam, LPARAM lParam, bool& bHandle);
    //Ӧ�þ���Ԥ������
    bool OnApplyMatrixSceneInd(WPARAM wParam, LPARAM lParam, bool& bHandle);

	APP_DECLARE_MSG_MAP()
private:
	CTouchListUI     *m_pInputList;
	CTouchListUI     *m_pOutputList;
};