type dataObject = {
  .
  "__typename": string,
  "id": string,
  "key": string
};

let cache = ApolloInMemoryCache.createInMemoryCache(~dataIdFromObject=(obj: dataObject) => obj##id, ());

let link = ApolloLinkSchema.make({"schema": Graphql.schema});

module Client =
  ReasonApollo.CreateClient(
    {
      let apolloClient =
        ReasonApollo.createApolloClient(~cache, ~link, ~ssrMode=Js.Boolean.to_js_boolean(true), ());
    }
  );
