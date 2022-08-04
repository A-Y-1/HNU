`timescale 1ns / 1ps

`include "../I2C_Tes/M24XXX_Memory.v"
`include "../I2C_Rtl/i2c.v"

module i2c_tb();

reg clk;
reg rstn;
reg write_op;
reg [7:0] write_data;
reg read_op;
wire [7:0] read_data;
reg [7:0] addr;

wire scl;
wire sda;

pullup(sda);
i2c i2c_dut(
 .clk (clk),
 .rstn(rstn),
 .write_op(write_op),
 .write_data(write_data),
 .read_op(read_op),
 .read_data(read_data),
 .addr(addr),
 .op_done(op_done),
 .scl(scl),
 .sda(sda)
);
//EEPROM
M24XXX M24XXX_dut(
	.Ei(3'b0),
	.SDA(sda),
	.SCL(scl),
	.WC(1'b0),
	.VCC(1'b1)
);

always #(166/2) clk = ~clk;					//6Mhz

initial
begin
	clk = 0;
	rstn = 0;
	write_op=1'b1;
	write_data=8'h00;
	read_op=1'b1;
	addr=0;
	
	repeat(5) @(posedge clk);
	rstn = 1'b1;
end

initial 
begin
	wait(rstn);
	repeat(10) @(posedge clk);
	write_op=1'b0;
	addr = 8'h55;
	write_data= 8'haa;
	
	wait(op_done);
	write_op=1'b1;
	$display ($stime/1,"ns","Write:Addr(%h)=(%h)\n",addr,write_data);
	
	wait(!op_done);
	repeat(100)@(posedge clk);
	read_op=1'b0;
	addr = 8'h55;
	wait(op_done);
	read_op=1'b1;
	$display ($stime/1,"ns","Read:Addr(%h)=(%h)\n",addr,read_data);
	
	repeat(1000) @(posedge clk);
	$stop;
end

endmodule
