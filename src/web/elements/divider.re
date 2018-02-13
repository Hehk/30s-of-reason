open Theme;

include (
  val NiceComponents.div(~debugName="divider", [|Height(Px(1)), BackgroundColor(Colors.red), Margin(Spacing.normal)|])
);
