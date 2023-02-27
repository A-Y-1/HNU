module control_signal_logic(mova,movb,movc,add,sub,and1,not1,rsr,rsl,jmp,jz,jc,in1,out1,nop,halt,ir,sm,z,c,reg_ra,reg_wa,madd,alu_s,pc_ld,pc_in,reg_we,ram_xl,ram_dl,alu_m,shi_fbus,shi_frbus,shi_flbus,ir_ld,cf_en,zf_en,sm_en,in_en,out_en);
	input mova,movb,movc,add,sub,and1,not1,rsr,rsl,jmp,jz,z,jc,c,in1,out1,nop,halt,sm;
	input [7:0]ir;
	output reg pc_ld,pc_in,reg_we,ram_xl,ram_dl,alu_m,shi_fbus,shi_frbus,shi_flbus,ir_ld,cf_en,zf_en,sm_en,in_en,out_en;
	output reg [1:0]reg_ra;
	output reg [1:0]reg_wa;
	output reg [1:0]madd;
	output reg [3:0]alu_s;
	always@(mova,movb,movc,add,sub,and1,not1,rsr,rsl,jmp,jz,z,jc,c,in1,out1,nop,halt,sm,ir)
	begin
		sm_en<=!halt;
		//
		alu_m<=add||sub||and1||not1||rsr||rsl||out1;
		cf_en<=add||sub||rsr||rsl;
		zf_en<=add||sub;
		alu_s[3:0]<=ir[7:4];
		//
		shi_fbus<=mova||movb||add||sub||and1||not1||out1;
		shi_frbus<=rsr;
		shi_flbus<=rsl;
		//
		ram_dl<=movc||jmp||(jz&&z)||(jc&&c)||!sm;
		ram_xl<=movb;
		//
		ir_ld<=!sm;
		//
		reg_we<=!(mova||movc||add||sub||and1||not1||rsl||rsr||in1)||!sm;
		reg_wa<=ir[3:2];
		reg_ra[1:0]<=ir[1:0];
		//
		pc_ld<=jmp||(jz&&z)||(jc&&c);
		pc_in<=(jz&&!z)||(jc&&!c)||!sm;
		//
		if(movb&&sm) madd<=2'b10;
		else if(movc&&sm) madd<=2'b01;	
		else if(!sm) madd<=2'b00;
		else madd<=2'b00;
		//in,out
		in_en<=in1;
		out_en<=out1;
 	end
endmodule
