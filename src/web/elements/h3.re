open Theme;

include (
  val NiceComponents.h3(~debugName="H3", [|Raw("font-size", Font.Size.normal), Margin(Px(0)), MarginBottom(Rem(1.))|])
);
