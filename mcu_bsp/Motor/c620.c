#include "C620.h"

// !C620的ID从1开始
C620_group_Controller_t *C620_Group_instnce[C620_GROUP_NUM] = {NULL}; // c620实例数组
static int idx = 0;                                                          // 由于C620的id从1开始的特性,故而实例从下标1开始,共有第几组3508电机

void C620_Group_Get_Info(CANInstance *can_instance)
{
    switch (can_instance->rx_id)
    {
    case 0x201:
    {
        ((C620_group_Controller_t *)(can_instance->id))->motor_instnce_1.get.deg_pos = (can_instance->rx_buff[0] << 8) + can_instance->rx_buff[1];
        ((C620_group_Controller_t *)(can_instance->id))->motor_instnce_1.get.velocity = (can_instance->rx_buff[2] << 8) + can_instance->rx_buff[3];
        ((C620_group_Controller_t *)(can_instance->id))->motor_instnce_1.get.current = (can_instance->rx_buff[4] << 8) + can_instance->rx_buff[5];
        break;
    }
    case 0x202:
    {
        ((C620_group_Controller_t *)(can_instance->id))->motor_instnce_2.get.deg_pos = (can_instance->rx_buff[0] << 8) + can_instance->rx_buff[1];
        ((C620_group_Controller_t *)(can_instance->id))->motor_instnce_2.get.velocity = (can_instance->rx_buff[2] << 8) + can_instance->rx_buff[3];
        ((C620_group_Controller_t *)(can_instance->id))->motor_instnce_2.get.current = (can_instance->rx_buff[4] << 8) + can_instance->rx_buff[5];
        break;
    }
    case 0x203:
    {
        ((C620_group_Controller_t *)(can_instance->id))->motor_instnce_3.get.deg_pos = (can_instance->rx_buff[0] << 8) + can_instance->rx_buff[1];
        ((C620_group_Controller_t *)(can_instance->id))->motor_instnce_3.get.velocity = (can_instance->rx_buff[2] << 8) + can_instance->rx_buff[3];
        ((C620_group_Controller_t *)(can_instance->id))->motor_instnce_3.get.current = (can_instance->rx_buff[4] << 8) + can_instance->rx_buff[5];
        break;
    }
    case 0x204:
    {
        ((C620_group_Controller_t *)(can_instance->id))->motor_instnce_4.get.deg_pos = (can_instance->rx_buff[0] << 8) + can_instance->rx_buff[1];
        ((C620_group_Controller_t *)(can_instance->id))->motor_instnce_4.get.velocity = (can_instance->rx_buff[2] << 8) + can_instance->rx_buff[3];
        ((C620_group_Controller_t *)(can_instance->id))->motor_instnce_4.get.current = (can_instance->rx_buff[4] << 8) + can_instance->rx_buff[5];
        break;
    }
    case 0x205:
    {
        ((C620_group_Controller_t *)(can_instance->id))->motor_instnce_1.get.deg_pos = (can_instance->rx_buff[0] << 8) + can_instance->rx_buff[1];
        ((C620_group_Controller_t *)(can_instance->id))->motor_instnce_1.get.velocity = (can_instance->rx_buff[2] << 8) + can_instance->rx_buff[3];
        ((C620_group_Controller_t *)(can_instance->id))->motor_instnce_1.get.current = (can_instance->rx_buff[4] << 8) + can_instance->rx_buff[5];
        break;
    }
    case 0x206:
    {
        ((C620_group_Controller_t *)(can_instance->id))->motor_instnce_2.get.deg_pos = (can_instance->rx_buff[0] << 8) + can_instance->rx_buff[1];
        ((C620_group_Controller_t *)(can_instance->id))->motor_instnce_2.get.velocity = (can_instance->rx_buff[2] << 8) + can_instance->rx_buff[3];
        ((C620_group_Controller_t *)(can_instance->id))->motor_instnce_2.get.current = (can_instance->rx_buff[4] << 8) + can_instance->rx_buff[5];
        break;
    }
    case 0x207:
    {
        ((C620_group_Controller_t *)(can_instance->id))->motor_instnce_3.get.deg_pos = (can_instance->rx_buff[0] << 8) + can_instance->rx_buff[1];
        ((C620_group_Controller_t *)(can_instance->id))->motor_instnce_3.get.velocity = (can_instance->rx_buff[2] << 8) + can_instance->rx_buff[3];
        ((C620_group_Controller_t *)(can_instance->id))->motor_instnce_3.get.current = (can_instance->rx_buff[4] << 8) + can_instance->rx_buff[5];
        break;
    }
    case 0x208:
    {
        ((C620_group_Controller_t *)(can_instance->id))->motor_instnce_4.get.deg_pos = (can_instance->rx_buff[0] << 8) + can_instance->rx_buff[1];
        ((C620_group_Controller_t *)(can_instance->id))->motor_instnce_4.get.velocity = (can_instance->rx_buff[2] << 8) + can_instance->rx_buff[3];
        ((C620_group_Controller_t *)(can_instance->id))->motor_instnce_4.get.current = (can_instance->rx_buff[4] << 8) + can_instance->rx_buff[5];
        break;
    }
    }
}
/**
 * @brief
 *
 * @param hcan ,表示can1还是can2
 * @param group_id, 表示can1的第几组c620电机
 * @param protocol_id 0x200 or 0x1FF
 */
void C620_Group_Register(CAN_HandleTypeDef *hcan, uint8_t group_id, uint32_t protocol_id)
{

    C620_group_Controller_t *C620_group_s = (C620_group_Controller_t *)malloc(sizeof(C620_group_Controller_t));
    C620_group_s->group_id = group_id;
    C620_group_s->protocol_id = protocol_id;
    CAN_Init_Config_s can_instance_config={0};
    memset(C620_group_s, 0, sizeof(C620_group_Controller_t));
    can_instance_config.can_handle = hcan;
    can_instance_config.tx_id = protocol_id;
    can_instance_config.can_module_callback = C620_Group_Get_Info;
    can_instance_config.id = C620_group_s;

    // 第一个电机
    can_instance_config.rx_id = (protocol_id == 0x200) ? 0x200 + 1 : 0x204 + 1;
    C620_group_s->can_instance_1 = CANRegister(&can_instance_config);
    // 第二个电机
    can_instance_config.rx_id = (protocol_id == 0x200) ? 0x200 + 2 : 0x204 + 2;
    C620_group_s->can_instance_2 = CANRegister(&can_instance_config);
    // 第三个电机
    can_instance_config.rx_id = (protocol_id == 0x200) ? 0x200 + 3 : 0x204 + 3;
    C620_group_s->can_instance_3 = CANRegister(&can_instance_config);
    // 第四个电机
    can_instance_config.rx_id = (protocol_id == 0x200) ? 0x200 + 4 : 0x204 + 4;
    C620_group_s->can_instance_4 = CANRegister(&can_instance_config);

    C620_Group_instnce[idx++] = C620_group_s;
}

static void C620_Group_base_current(uint8_t group_id)
{

    if (MOTOR_STOP == C620_Group_instnce[group_id]->motor_instnce_1.motor_cofig.motor_enable_flag)
    {
        C620_Group_instnce[group_id]->motor_instnce_1.set.current = 0;
    }
    else
    {
        if (MOTOR_DIRECTION_REVERSE == C620_Group_instnce[group_id]->motor_instnce_1.motor_cofig.motor_reverse_flag)
        {
            MOTOR_VAR_REVERSE(C620_Group_instnce[group_id]->motor_instnce_1.set.current);
        }
    }

    if (MOTOR_STOP == C620_Group_instnce[group_id]->motor_instnce_2.motor_cofig.motor_enable_flag)
    {
        C620_Group_instnce[group_id]->motor_instnce_2.set.current = 0;
    }
    else
    {
        if (MOTOR_DIRECTION_REVERSE == C620_Group_instnce[group_id]->motor_instnce_2.motor_cofig.motor_reverse_flag)
        {
            MOTOR_VAR_REVERSE(C620_Group_instnce[group_id]->motor_instnce_2.set.current);
        }
    }

    if (MOTOR_STOP == C620_Group_instnce[group_id]->motor_instnce_3.motor_cofig.motor_enable_flag)
    {
        C620_Group_instnce[group_id]->motor_instnce_3.set.current = 0;
    }
    else
    {
        if (MOTOR_DIRECTION_REVERSE == C620_Group_instnce[group_id]->motor_instnce_3.motor_cofig.motor_reverse_flag)
        {
            MOTOR_VAR_REVERSE(C620_Group_instnce[group_id]->motor_instnce_3.set.current);
        }
    }

    if (MOTOR_STOP == C620_Group_instnce[group_id]->motor_instnce_4.motor_cofig.motor_enable_flag)
    {
        C620_Group_instnce[group_id]->motor_instnce_4.set.current = 0;
    }
    else
    {
        if (MOTOR_DIRECTION_REVERSE == C620_Group_instnce[group_id]->motor_instnce_4.motor_cofig.motor_reverse_flag)
        {
            MOTOR_VAR_REVERSE(C620_Group_instnce[group_id]->motor_instnce_4.set.current);
        }
    }
}

void C620_Group_Set_Current(uint8_t group_id)
{
    C620_Group_base_current(group_id);
    uint8_t motor_current_data[8] = {0};

    motor_curren`t_data[0] = (int16_t)C620_Group_instnce[group_id]->motor_instnce_1.set.current >> 8;
    motor_current_data[1] = (int16_t)C620_Group_instnce[group_id]->motor_instnce_1.set.current ;
    motor_current_data[2] = (int16_t)C620_Group_instnce[group_id]->motor_instnce_2.set.current >> 8;
    motor_current_data[3] = (int16_t)C620_Group_instnce[group_id]->motor_instnce_2.set.current ;
    motor_current_data[4] = (int16_t)C620_Group_instnce[group_id]->motor_instnce_3.set.current >> 8;
    motor_current_data[5] = (int16_t)C620_Group_instnce[group_id]->motor_instnce_3.set.current ;
    motor_current_data[6] = (int16_t)C620_Group_instnce[group_id]->motor_instnce_4.set.current >> 8;
    motor_current_data[7] = (int16_t)C620_Group_instnce[group_id]->motor_instnce_4.set.current ;

    memcpy(C620_Group_instnce[group_id]->can_instance_1->tx_buff, motor_current_data,8);
    CANTransmit(C620_Group_instnce[group_id]->can_instance_1);
}
