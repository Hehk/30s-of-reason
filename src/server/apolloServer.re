type dataObject = {
  .
  "__typename": string,
  "id": string,
  "key": string
};

let cache =
  ApolloInMemoryCache.createInMemoryCache(
    ~dataIdFromObject=(obj: dataObject) => obj##id,
    ()
  );

let link =
  ApolloLinkSchema.make({
    "schema": GraphQLTools.makeExecutableSchema(Graphql.schema)
  });

module Client =
  ReasonApollo.CreateClient(
    {
      let apolloClient =
        ReasonApollo.createApolloClient(~cache, ~link, ~ssrMode=Js.true_, ());
    }
  );
