`timescale 1ns / 1ps
module i2c(
	input clk,					//时钟
	input rstn,				//复位
	input write_op,				//写操作
	input [7:0]write_data,			//写入的数据
	input read_op,				//读操作
	output reg [7:0]read_data,			//读出的数据
	input [7:0]addr,				//地址
	output op_done,				//操作结束
	output reg scl,				//scl
	inout sda					//sda
);
//I2C状态
parameter IDLE =8'h00,
		  WAIT_WTICK0=8'h01,
		  WAIT_WTICK1=8'h02,
		  W_START=8'h03,
		  W_DEVICE7=8'h04,
		  W_DEVICE6=8'h05,
		  W_DEVICE5=8'h06,
		  W_DEVICE4=8'h07,
		  W_DEVICE3=8'h08,
		  W_DEVICE2=8'h09,
		  W_DEVICE1=8'h0a,
		  W_DEVICE0=8'h0b,
		  W_DEVACK=8'h0c,
		  W_ADDRES7=8'h0d,
		  W_ADDRES6=8'h0e,
		  W_ADDRES5=8'h0f,
		  W_ADDRES4=8'h10,
		  W_ADDRES3=8'h11,
		  W_ADDRES2=8'h12,
		  W_ADDRES1=8'h13,
		  W_ADDRES0=8'h14,
		  W_AACK=8'h15,
		  W_DATA7=8'h16,
		  W_DATA6=8'h17,
		  W_DATA5=8'h18,
		  W_DATA4=8'h19,
		  W_DATA3=8'h1a,
		  W_DATA2=8'h1b,
		  W_DATA1=8'h1c,
		  W_DATA0=8'h1d,
		  W_DACK=8'h1e,
		  WAIT_WTICK3=8'h1f,
		  R_START=8'h20,
		  R_DEVICE7=8'h21,
		  R_DEVICE6=8'h22,
		  R_DEVICE5=8'h23,
		  R_DEVICE4=8'h24,
		  R_DEVICE3=8'h25,
		  R_DEVICE2=8'h26,
		  R_DEVICE1=8'h27,
		  R_DEVICE0=8'h28,
		  R_DACK=8'h29,
		  R_DATA7=8'h2a,
		  R_DATA6=8'h2b,
		  R_DATA5=8'h2c,
		  R_DATA4=8'h2d,
		  R_DATA3=8'h2e,
		  R_DATA2=8'h2f,
		  R_DATA1=8'h30,
		  R_DATA0=8'h31,
		  R_NOACK=8'h32,
		  S_STOP=8'h33,
		  S_STOP0=8'h34,
		  S_STOP1=8'h35,
		  W_OPOVER=8'h36;
		  
reg [7:0]i2c,next_i;					//当前状态，下一状态
reg [7:0]div_cnt;					//计数器
wire scl_tick;
//计数
always @(posedge clk or negedge rstn)
if(!rstn) div_cnt <=8'd0;
else if((i2c==IDLE)|scl_tick) div_cnt <=8'd0;
else div_cnt<=div_cnt+1'b1;
//scl同步
wire scl_ls =(div_cnt==8'd0);				//scl low
wire scl_lc = (div_cnt==8'd7);				//scl low center
wire scl_hs =(div_cnt==8'd15);			//scl high
wire scl_hc = (div_cnt==8'd22);			//scl high center
assign scl_tick = (div_cnt==8'd29);			//一个周期结束
//状态
always @(posedge clk or negedge rstn)
if(!rstn) i2c <=0;
else i2c <= next_i;

//Byte Write : START + DEVICE +ACK + ADDR + ACK + DATA + ACK + STOP
//Random Read : START + DEVICE + ACK +ADDR + START + DEVICE + DATA + NO ACK + STOP
reg wr_op,rd_op;					//读写操作

always @ (posedge clk or negedge rstn)
if(!rstn) wr_op <= 0;
else if (i2c==IDLE) wr_op <= ~write_op;
else if(i2c==W_OPOVER) wr_op <=1'b0;

always @(posedge clk or negedge rstn)
if(!rstn) rd_op <= 0;
else if (i2c==IDLE) rd_op <= ~read_op;
else if(i2c==W_OPOVER) rd_op <=1'b0;

wire  d5ms_over;

//下一状态判断
always@(*)
case (i2c)
	IDLE: begin next_i = IDLE;if(wr_op|rd_op) next_i = WAIT_WTICK0;end		//有读写操作跳出空闲状态

	//wait tick
	WAIT_WTICK0:begin next_i = WAIT_WTICK0;if(scl_tick) next_i=WAIT_WTICK1;end	
	WAIT_WTICK1:begin next_i = WAIT_WTICK1;if(scl_tick) next_i = W_START;end
	
	//START:SCL=1,SDA=1->0(scl_lc)
	W_START:begin next_i=W_START;if(scl_tick) next_i=W_DEVICE7;end
	
	//DEVICE ADDRESS（1010_000_0(WRITE)）
	W_DEVICE7:begin next_i = W_DEVICE7;if(scl_tick) next_i=W_DEVICE6;end
	W_DEVICE6:begin next_i = W_DEVICE6;if(scl_tick) next_i=W_DEVICE5;end
	W_DEVICE5:begin next_i = W_DEVICE5;if(scl_tick) next_i=W_DEVICE4;end
	W_DEVICE4:begin next_i = W_DEVICE4;if(scl_tick) next_i=W_DEVICE3;end
	W_DEVICE3:begin next_i = W_DEVICE3;if(scl_tick) next_i=W_DEVICE2;end
	W_DEVICE2:begin next_i = W_DEVICE2;if(scl_tick) next_i=W_DEVICE1;end
	W_DEVICE1:begin next_i = W_DEVICE1;if(scl_tick) next_i=W_DEVICE0;end
	W_DEVICE0:begin next_i = W_DEVICE0;if(scl_tick) next_i=W_DEVACK;end
	
	//ACK
	W_DEVACK:begin next_i=W_DEVACK;if(scl_tick) next_i=W_ADDRES7;end
	
	//WORD ADDRESS
	W_ADDRES7 :begin next_i = W_ADDRES7;if(scl_tick) next_i=W_ADDRES6;end
	W_ADDRES6 :begin next_i = W_ADDRES6;if(scl_tick) next_i=W_ADDRES5;end
	W_ADDRES5 :begin next_i = W_ADDRES5;if(scl_tick) next_i=W_ADDRES4;end
	W_ADDRES4 :begin next_i = W_ADDRES4;if(scl_tick) next_i=W_ADDRES3;end
	W_ADDRES3 :begin next_i = W_ADDRES3;if(scl_tick) next_i=W_ADDRES2;end
	W_ADDRES2 :begin next_i = W_ADDRES2;if(scl_tick) next_i=W_ADDRES1;end
	W_ADDRES1 :begin next_i = W_ADDRES1;if(scl_tick) next_i=W_ADDRES0;end
	W_ADDRES0 :begin next_i = W_ADDRES0;if(scl_tick) next_i=W_AACK;end
	
	//ACK
	W_AACK:begin next_i = W_AACK;
				 if(scl_tick&wr_op) next_i=W_DATA7;			//wr_op即写命令，开始写数据
				 else if(scl_tick&rd_op) next_i=WAIT_WTICK3;		//rd_op读命令,则下一状态为WAIT_WTICK3
		   end
	
	//WRITE DATA[7:0]
	W_DATA7:begin next_i=W_DATA7;if(scl_tick)next_i=W_DATA6;end
	W_DATA6:begin next_i=W_DATA6;if(scl_tick)next_i=W_DATA5;end
	W_DATA5:begin next_i=W_DATA5;if(scl_tick)next_i=W_DATA4;end
	W_DATA4:begin next_i=W_DATA4;if(scl_tick)next_i=W_DATA3;end
	W_DATA3:begin next_i=W_DATA3;if(scl_tick)next_i=W_DATA2;end
	W_DATA2:begin next_i=W_DATA2;if(scl_tick)next_i=W_DATA1;end
	W_DATA1:begin next_i=W_DATA1;if(scl_tick)next_i=W_DATA0;end
	W_DATA0:begin next_i=W_DATA0;if(scl_tick)next_i=W_DACK;end
	
	//ACK
	W_DACK:begin next_i=W_DACK; if(scl_tick) next_i=S_STOP;end
	
	//Current Address Read
	//START: SCL=1,SDA=1->0(scl_lc)
	
	WAIT_WTICK3:begin next_i=WAIT_WTICK3; if(scl_tick) next_i=R_START;end
	R_START:begin next_i=R_START; if(scl_tick)next_i=R_DEVICE7;end
	
	//DEVICE ADDRESS(1010_000_1(READ)) 
	R_DEVICE7:begin next_i=R_DEVICE7; if(scl_tick) next_i=R_DEVICE6;end
	R_DEVICE6:begin next_i=R_DEVICE6; if(scl_tick) next_i=R_DEVICE5;end
	R_DEVICE5:begin next_i=R_DEVICE5; if(scl_tick) next_i=R_DEVICE4;end
	R_DEVICE4:begin next_i=R_DEVICE4; if(scl_tick) next_i=R_DEVICE3;end
	R_DEVICE3:begin next_i=R_DEVICE3; if(scl_tick) next_i=R_DEVICE2;end
	R_DEVICE2:begin next_i=R_DEVICE2; if(scl_tick) next_i=R_DEVICE1;end
	R_DEVICE1:begin next_i=R_DEVICE1; if(scl_tick) next_i=R_DEVICE0;end
	R_DEVICE0:begin next_i=R_DEVICE0; if(scl_tick) next_i=R_DACK;end
	
	//ACK
	R_DACK:begin next_i=R_DACK;if(scl_tick) next_i=R_DATA7;end
	
	//READ DATA[7:0], SDA:input
	R_DATA7:begin next_i=R_DATA7;if(scl_tick) next_i=R_DATA6;end
	R_DATA6:begin next_i=R_DATA6;if(scl_tick) next_i=R_DATA5;end
	R_DATA5:begin next_i=R_DATA5;if(scl_tick) next_i=R_DATA4;end
	R_DATA4:begin next_i=R_DATA4;if(scl_tick) next_i=R_DATA3;end
	R_DATA3:begin next_i=R_DATA3;if(scl_tick) next_i=R_DATA2;end
	R_DATA2:begin next_i=R_DATA2;if(scl_tick) next_i=R_DATA1;end
	R_DATA1:begin next_i=R_DATA1;if(scl_tick) next_i=R_DATA0;end
	R_DATA0:begin next_i=R_DATA0;if(scl_tick) next_i=R_NOACK;end
	
	//NO ACK
	R_NOACK:begin next_i=R_NOACK;if(scl_tick) next_i=S_STOP;end
	
	//STOP
	S_STOP:begin next_i=S_STOP;if(scl_tick) next_i=S_STOP0;end
	S_STOP0:begin next_i=S_STOP0;if(scl_tick) next_i=S_STOP1;end
	S_STOP1:begin next_i=S_STOP1;if(scl_tick) next_i=W_OPOVER;end			
	
	//WAIT write_op=0,read_op=0;
	W_OPOVER:begin next_i = W_OPOVER;if(d5ms_over)next_i=IDLE;end		//操作结束回到空闲状态
	default:begin next_i= IDLE;end
endcase

//SCL
assign clr_scl=scl_ls&(i2c!=IDLE)&(i2c!=WAIT_WTICK0)&					//clr_scl，scl置0信号
			   (i2c != WAIT_WTICK1)&(i2c!=W_START)&(i2c!=R_START)
			   &(i2c!=S_STOP0)&(i2c!=S_STOP1)&(i2c!=W_OPOVER);

always @(posedge clk or negedge rstn)
if(!rstn) scl <= 1'b1;									//复位，scl为高电平
else if(clr_scl) scl <= 1'b0;								//scl 1->0
else if(scl_hs) scl <=1'b1;								//scl 0->1

//SDA
reg [7:0]i2c_reg;
assign start_clr = scl_lc &((i2c==W_START)|(i2c==R_START));				//在scl low center开始读写操作
assign ld_wdevice = scl_lc&(i2c==W_DEVICE7);						//加载器件地址
assign ld_waddres = scl_lc&(i2c==W_ADDRES7);						//加载数据地址
assign ld_wdata= scl_lc&(i2c==W_DATA7);						//加载数据
assign ld_rdevice = scl_lc&(i2c==R_DEVICE7);						//读操作的器件地址
assign noack_set = scl_lc&(i2c==R_NOACK);						//读操作完毕
assign stop_clr = scl_lc&(i2c==S_STOP);						
assign stop_set = scl_lc&((i2c==S_STOP0)|(i2c==WAIT_WTICK3));

assign i2c_rlf =scl_lc&(								//有读写则i2c_rlf
				(i2c == W_DEVICE6)|
				(i2c == W_DEVICE5)|
				(i2c == W_DEVICE4)|
				(i2c == W_DEVICE3)|
				(i2c == W_DEVICE2)|
				(i2c == W_DEVICE1)|
				(i2c == W_DEVICE0)|
				(i2c == W_ADDRES6)|
				(i2c == W_ADDRES5)|
				(i2c == W_ADDRES4)|
				(i2c == W_ADDRES3)|
				(i2c == W_ADDRES2)|
				(i2c == W_ADDRES1)|
				(i2c == W_ADDRES0)|
				(i2c == W_DATA6)|
				(i2c == W_DATA5)|
				(i2c == W_DATA4)|
				(i2c == W_DATA3)|
				(i2c == W_DATA2)|
				(i2c == W_DATA1)|
				(i2c == W_DATA0)|
				(i2c == R_DEVICE6)|
				(i2c == R_DEVICE5)|
				(i2c == R_DEVICE4)|
				(i2c == R_DEVICE3)|
				(i2c == R_DEVICE2)|
				(i2c == R_DEVICE1)|
				(i2c == R_DEVICE0));

always@(posedge clk or negedge rstn)
if(!rstn) i2c_reg <= 8'hff;								//复位，高电平
else if(start_clr) i2c_reg <= 8'h00;							//开始读写，低电平
else if(ld_wdevice) i2c_reg <= {4'b1010,3'b000,1'b0};					//10100000 写
else if(ld_waddres) i2c_reg <= addr;							//加载数据地址
else if(ld_wdata) i2c_reg <= write_data;							//加载写入的数据
else if(ld_rdevice) i2c_reg <= {4'b1010,3'b000,1'b1};					//10100001 读
else if(noack_set) i2c_reg <= 8'hff;							//NOACK
else if(stop_clr) i2c_reg <= 8'h00;
else if(stop_set) i2c_reg <= 8'hff;
else if(i2c_rlf) i2c_reg <= {i2c_reg[6:0],1'b0};						//左移

assign sda_o = i2c_reg[7];								//sda输出
assign clr_sdaen = (i2c==IDLE)|							//sda使能置0信号
				   (scl_lc&(
				   (i2c==W_DEVACK)|
				   (i2c==W_AACK)|
				   (i2c==W_DACK)|
				   (i2c==R_DACK)|
				   (i2c==R_DATA7)));

assign set_sdaen = scl_lc&(								//sda使能置1信号
				   (i2c==WAIT_WTICK0)|
				   (i2c==W_ADDRES7)|
				   (i2c==W_DATA7)|
				   (i2c==WAIT_WTICK3)|
				   (i2c==S_STOP)|
				   (i2c==R_NOACK));

reg sda_en;
always @(posedge clk or negedge rstn)
if(!rstn) sda_en <= 0;								
else if (clr_sdaen) sda_en <=0;
else if(set_sdaen) sda_en <= 1'b1;

assign sda= sda_en?sda_o: 1'bz;							//sda使能为1时sda可工作

assign sda_wr = scl_hc &(								//读数据
				(i2c==R_DATA7)|
				(i2c==R_DATA6)|
				(i2c==R_DATA5)|
				(i2c==R_DATA4)|
				(i2c==R_DATA3)|
				(i2c==R_DATA2)|
				(i2c==R_DATA1)|
				(i2c==R_DATA0));

always@(posedge clk or negedge rstn)
if(!rstn) read_data <= 0;
else if(sda_wr) read_data <= {read_data[6:0],sda};					//左移读入数据

//op_done
assign op_done = (i2c == W_OPOVER);						//操作结束

//Write Cycle(5ms)
//6MHZ = 166ns,5ms/166ns = 31
reg [12:0] d5ms_cnt;
always @(posedge clk or negedge rstn)
if(!rstn)    d5ms_cnt <= 8'd0;
else if(i2c==IDLE) d5ms_cnt <= 8'd0;
else if(i2c==W_OPOVER) d5ms_cnt <= d5ms_cnt + 1'b1;

assign d5ms_over = (d5ms_cnt==13'h1FFF);
				
endmodule
	
	
	