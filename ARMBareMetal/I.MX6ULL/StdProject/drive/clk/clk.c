#include "clk.h"

// 使能外设时钟函数
void CLK_Enable(void)
{
    CCM->CCGR0 = 0XFFFFFFFF;
    CCM->CCGR1 = 0XFFFFFFFF;
    CCM->CCGR2 = 0XFFFFFFFF;
    CCM->CCGR3 = 0XFFFFFFFF;
    CCM->CCGR4 = 0XFFFFFFFF;
    CCM->CCGR5 = 0XFFFFFFFF;
    CCM->CCGR6 = 0XFFFFFFFF;
}

void CLK_Init(void)
{
    // 配置时钟系统主频为792MHz
    // 1.判断当前时钟,判断CCM_CCSR寄存器的PLL1_SW_CLK_SEL位
    if ((((CCM->CCSR) >> 2) & 0X1) == 0) // pll1_main_clk
    {
        // 将step_clk的时钟源切换为osc_clk,配置CCSR寄存器的step_sel位.
        CCM->CCSR &= ~(1 << 8);
        // 将系统时钟源切换为step_clk.配置CCM_CCSR寄存器的PLL1_SW_CLK_SEL位
        CCM->CCSR |= (1 << 2);
    }
    // 2.配置PLL1频率.根据公式配置为792MHz要配置CCM_ANALOG_PLL_ARM寄存器的[DIV_SELECT]位的值为66
    CCM_ANALOG->PLL_ARM = (1 << 13) | ((66 << 0) & 0X7F);
    // 3.配置分频器
    CCM->CACRR = 0X0; // CACRR寄存器只有位0~位2有效,要配置一分频就是0,直接让这个寄存器全部等于0即可.
                      // 4.切换回pll1_main_clk.
    CCM->CCSR &= ~(1 << 2);

    // 配置PLL2_PFD0~PLL2_PFD3频率
    uint32_t PFD_Reg;
    PFD_Reg = CCM_ANALOG->PFD_528;
    PFD_Reg &= 0XC0C0C0C0; // PFD0~PFD3对应位清零
    PFD_Reg |= ((27 << 0) | (16 << 8) | (24 << 16) | (32 << 24));
    //          PFD0:352MHz PFD1:594MHz PFD2:396MHz  PFD2:297MHz
    CCM_ANALOG->PFD_528 = PFD_Reg;

    // 配置PLL3_PFD0~PLL3_PFD3频率
    PFD_Reg = CCM_ANALOG->PFD_480;
    PFD_Reg &= 0XC0C0C0C0;
    PFD_Reg |= (12 << 0) | (16 << 8) | (17 << 16) | (19 << 24);
    //          PFD0:720MHz PFD1:540MHz PFD2:508.2MHz  PFD2:454.7MHz
    CCM_ANALOG->PFD_480 = PFD_Reg;

    // 配置AHBAHB_CLK_ROOT频率为132MHz
        // 配置CBCMR寄存器[PRE_PERIPH_CLK_SEL]位.选择PLL2 PFD2作为输入时钟源
    CCM->CBCMR &= ~(3 << 18); //[PRE_PERIPH_CLK_SEL]位 清零
    CCM->CBCMR |= (1 << 18);  // 位19位18 赋值为0 1
        // 配置CBCDR寄存器的[PERIPH_CLK_SEL]位.
    CCM->CBCDR &= ~(1 << 25); // 选择pll2_main_clk
    while (CCM->CDHIPR & (1 << 5))
        ; // 检查握手信号,直到握手信号不忙

#if 0
        // 配置CBCDR寄存器的[AHB_PODF]位,进行分频
    CCM->CBCDR &= ~(7 << 10); // 对应位清零
    CCM->CBCDR |= (2 << 10);  // 设置三分频
    while (CCM->CDHIPR & (1 << 1))
        ; // 检查握手信号,直到握手信号不忙
#endif    // 0
    //配置IPG_CLK_ROOT频率为66MHz
        //配置分频器,CBCDR寄存器的[IPG_PODF]位
    CCM->CBCDR &= ~(3 << 8);//对应位清零
    CCM->CBCDR |= (1 << 8);//2分频
    //配置PERCLK_CLK_ROOT频率为66MHz.
        //配置多路选择器.配置CSCMR1寄存器的[PERCLK_CLK_SEL]位(位6).
    CCM->CSCMR1 &= ~(1 << 6);//配置为选择ipg_clk    
        //配置分频器,选择一分频.配置CSCMR1寄存器的[PERCLK_PODF]位(位0~位5).
    CCM->CSCMR1 &= ~(0X3F << 0);//对应位清零,配置为1分频
}
