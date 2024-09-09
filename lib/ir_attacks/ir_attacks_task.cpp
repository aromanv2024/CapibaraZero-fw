#include "ir_attacks_types.h"
#include "IrFramework.hpp"

void ir_record_signal_task(void *pv) {
    IrAttackTaskParams *params = static_cast<IrAttackTaskParams *>(pv);
    IrFramework *ir_framework = params->ir_framework;
    while(!ir_framework->read_signal()) {
        NOP();
    }
    RecordedSignal data = ir_framework->get_decoded_signal();
    Serial.println("Signal decoded successfully");
    Serial.println(data.protocol);
    if(data.protocol == 0)  // Unknown
        params->page->set_signal(ir_framework->enum_to_str(data.protocol), -1, -1, data.raw_len);
    else
        params->page->set_signal(ir_framework->enum_to_str(data.protocol), -1, -1, data.raw_len);
    vTaskDelete(NULL);
}