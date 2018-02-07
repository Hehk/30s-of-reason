include (
  val NiceComponents.div(
        ~debugName="Card",
        [
          Raw("box-shadow", "0 10px 40px 0 rgba(62,57,107,0.07), 0 2px 9px 0 rgba(62,57,107,0.06)"),
          BackgroundColor(White),
          BorderRadius(Px(3)),
          Margin(Px(0)),
          Raw("margin-top", "1rem"),
          Raw("margin-bottom", "1rem"),
          Raw("padding", "1rem"),
        ]
      )
);