module instruction_decoder(EN,ir,MOVA,MOVB,MOVC,ADD,SUB,AND1,NOT1,RSR,RSL,JMP,JZ,JC,IN1,OUT1,NOP,HALT);
	input [7:0] ir;
	input EN;
	output MOVA,MOVB,MOVC,ADD,SUB,AND1,NOT1,RSR,RSL,JMP,JZ,JC,IN1,OUT1,NOP,HALT;
	reg MOVA,MOVB,MOVC,ADD,SUB,AND1,NOT1,RSR,RSL,JMP,JZ,JC,IN1,OUT1,NOP,HALT;
	always@(ir,EN)
	begin
	MOVA=0;MOVB=0;MOVC=0;ADD=0;SUB=0;AND1=0;NOT1=0;RSR=0;RSL=0;JMP=0;JZ=0;JC=0;IN1=0;OUT1=0;NOP=0;HALT=0;
		if (EN)
		begin 
			if(ir[7:4]==4'b1100)
			begin
				if(ir[3]&ir[2]) MOVB=1;
				else if(ir[1]&ir[0]) MOVC=1;
				else MOVA=1'b1;
			end
			else if(ir[7:4]==4'b1001) ADD=1;
			else if(ir[7:4]==4'b0110) SUB=1;
			else if(ir[7:4]==4'b1011) AND1=1;
			else if(ir[7:4]==4'b0101) NOT1=1;
			else if(ir[7:4]==4'b1010)
			begin
				if(~ir[1]&~ir[0]) RSR=1;
				else RSL=1;
			end
			else if(ir[7:4]==4'b0011)
			begin
				JC=ir[1];
				JZ=ir[0];
				JMP=!ir[1]&&!ir[0];
			end
			else if(ir[7:4]==4'b0010)IN1=1;
			else if(ir[7:4]==4'b0100)OUT1=1;
			else if(ir[7:4]==4'b0111)NOP=1;
			else if(ir[7:4]==4'b1000) HALT=1;
			else ;
		end
		else ;
	end
endmodule