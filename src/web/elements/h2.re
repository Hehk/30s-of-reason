open Theme;

include (
  val NiceComponents.h2(
        ~debugName="H2",
        [|
          Raw("font-size", Font.Size.large),
          Margin(Spacing.none),
          MarginBottom(Spacing.normal),
          MarginTop(Spacing.large),
          Color(Colors.red)
        |]
      )
);
