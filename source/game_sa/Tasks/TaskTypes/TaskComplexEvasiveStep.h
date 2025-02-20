#pragma once

#include "TaskComplex.h"
class CEntity;

class CTaskComplexEvasiveStep : public CTaskComplex {
public:
    CVector  m_Pos;
    CEntity* m_Entity;

public:
    static constexpr auto Type = TASK_COMPLEX_EVASIVE_STEP;

    CTaskComplexEvasiveStep(CEntity* entity, const CVector& pos);
    ~CTaskComplexEvasiveStep() override;

    eTaskType GetTaskType() override { return Type; }
    CTask* Clone() override { return new CTaskComplexEvasiveStep(m_Entity, m_Pos); }
    CTask* CreateNextSubTask(CPed* ped) override;
    CTask* CreateFirstSubTask(CPed* ped) override;
    CTask* ControlSubTask(CPed* ped) override { return m_pSubTask; } // 0x653550

    CTask* CreateSubTask(eTaskType taskType);
};
VALIDATE_SIZE(CTaskComplexEvasiveStep, 0x1C);
