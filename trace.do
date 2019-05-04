cd build

vcd2wlf trace.vcd trace_modelsim.wlf
vsim -view trace_modelsim.wlf
view wave


# -radix: binary, hex, dec
# -label: nome da forma de onda

add wave	-radix binary		-label clock				/SystemC/nea/clock
add wave	-radix dec			-label uc_1.main_state		/SystemC/nea/cu/main_state
add wave	-radix dec			-label uc_1.pc_data_out		/SystemC/nea/pc_data_out
add wave	-radix binary		-label uc_1.mem_addr_sel	/SystemC/nea/mem_addr_sel
add wave	-radix dec			-label uc_1.mem_data_out	/SystemC/nea/mem_data_out
add wave	-radix binary		-label uc_1.mem_rd			/SystemC/nea/mem_rd
add wave	-radix binary		-label uc_1.mem_wr			/SystemC/nea/mem_wr
add wave	-radix dec			-label uc_1.mem_addr_in		/SystemC/nea/mem_addr_in
add wave	-radix binary		-label ac_load				/SystemC/nea/ac_load
add wave	-radix dec			-label ac_data_out			/SystemC/nea/ac_data_out
add wave	-radix dec			-label ula_op				/SystemC/nea/ula_op
add wave	-radix dec			-label ula_result			/SystemC/nea/ula_result
add wave	-radix dec			-label ula_input_a			/SystemC/nea/ula/input_a
add wave	-radix dec			-label ula_input_b			/SystemC/nea/ula/input_b
add wave	-radix binary		-label ula_op_now			/SystemC/nea/ula_op_now


wave zoom full